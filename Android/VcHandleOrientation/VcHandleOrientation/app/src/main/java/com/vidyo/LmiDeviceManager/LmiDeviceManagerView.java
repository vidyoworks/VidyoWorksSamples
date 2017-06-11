/**
{file:
{name: LmiDeviceManagerView.java}
	{description: Sample of a video renderer. }
	{copyright:
		(c) 2006-2009 Vidyo, Inc.,
		433 Hackensack Avenue, 6th Floor,
		Hackensack, NJ  07601.
		All rights reserved.
		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.}
}
 */
package com.vidyo.LmiDeviceManager;

import java.lang.reflect.Method;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class LmiDeviceManagerView extends GLSurfaceView {
	private static String TAG = "LmiDeviceManagerView";
	private static final boolean DEBUG = false;
	private static final int INVALID_POINTER_ID = -1;
	private static final int TOUCH_START = 0;
	private static final int TOUCH_STOP = 1;
	private static final int TOUCH_MOVE = 2;

	public enum RenderType { RENDER_RGBA_8888, RENDER_RGBA_5650, };

	Renderer bcRenderer;

	public interface Callback {
		public void LmiDeviceManagerViewRender();

		public void LmiDeviceManagerViewResize(int width, int height);

		public void LmiDeviceManagerViewRenderRelease();

		public void LmiDeviceManagerViewTouchEvent(int id, int type, int x, int y);		
	}

	public LmiDeviceManagerView(Context context, Callback callback) {
		this(context, callback, RenderType.RENDER_RGBA_8888);
	}
	
	public LmiDeviceManagerView(Context context, Callback callback, RenderType renderType) {
		super(context);
		setEGLContextFactory(new ContextFactory());

    	if (renderType == RenderType.RENDER_RGBA_8888) {
			try {
				setEGLConfigChooser(new ConfigChooser(8, 8, 8, 8, 16, 1));
				getHolder().setFormat(PixelFormat.RGBA_8888);
//				if (forceOnTop)
//					setZOrderOnTop(true);
			} catch (Exception ex ) {
				setEGLConfigChooser(new ConfigChooser(5, 6, 5, 0, 16, 1));
			}
		} else {
			setEGLConfigChooser(new ConfigChooser(5, 6, 5, 0, 16, 1));
		}

		
		/* Set the renderer responsible for frame rendering */
		bcRenderer = new Renderer();
		setRenderer(bcRenderer);
		bcRenderer.SetCallback(callback);
	}

	public void onPause() {
		super.onPause();
	}

	public void onResume() {
		super.onResume();
	}
	
	public void onDestroy() {
		if (bcRenderer != null) {
			bcRenderer.SetCallback(null);
			bcRenderer = null;
		}
	}
	
	private void dumpEvent(MotionEvent event) {
	   String names[] = { "DOWN" , "UP" , "MOVE" , "CANCEL" , "OUTSIDE" ,   "POINTER_DOWN" , "POINTER_UP" , "7?" , "8?" , "9?" };
	   StringBuilder sb = new StringBuilder();
	   int action = event.getAction();
	   int actionCode = action & MotionEvent.ACTION_MASK;
	   sb.append("event ACTION_" ).append(names[actionCode]);
	   if (actionCode == MotionEvent.ACTION_POINTER_DOWN  || actionCode == MotionEvent.ACTION_POINTER_UP) {
	      sb.append("(pid " ).append(
	      action >> MotionEvent.ACTION_POINTER_ID_SHIFT);
	      sb.append(")" );
	   }
	   
	   sb.append("[" );
	   for (int i = 0; i < event.getPointerCount(); i++) {
	      sb.append("#" ).append(i);
	      sb.append("(pid " ).append(event.getPointerId(i));
	      sb.append(")=" ).append((int) event.getX(i));
	      sb.append("," ).append((int) event.getY(i));
	      if (i + 1 < event.getPointerCount())
	         sb.append(";" );
	   }
	   sb.append("]" );
	   Log.d(TAG, sb.toString());
	}
	
	public boolean onTouchEvent(MotionEvent event) {		
		final int action = event.getAction();										
		int idx;
						
		switch (action & MotionEvent.ACTION_MASK) {
		case MotionEvent.ACTION_DOWN:						
			bcRenderer.TouchEvent(event.getPointerId(0), TOUCH_START, (int)event.getX(), (int) event.getY());			
			return true;
		case MotionEvent.ACTION_UP:					
			bcRenderer.TouchEvent(event.getPointerId(0), TOUCH_STOP, (int) event.getX(), (int) event.getY());			
			return true;
		case MotionEvent.ACTION_MOVE:
			for (idx = 0; idx < event.getPointerCount(); idx++) {			
				bcRenderer.TouchEvent(event.getPointerId(idx), TOUCH_MOVE, (int) event.getX(idx), (int) event.getY(idx));				
			}
			return true;
		case MotionEvent.ACTION_POINTER_DOWN:				
			idx = (action & MotionEvent.ACTION_POINTER_ID_MASK) >> MotionEvent.ACTION_POINTER_ID_SHIFT;			
			bcRenderer.TouchEvent(event.getPointerId(idx), TOUCH_START, (int) event.getX(idx), (int) event.getY(idx));			
			return true;
	    case MotionEvent.ACTION_POINTER_UP:
	        /* Extract the index of the pointer that left the touch sensor */
	    	idx = (action & MotionEvent.ACTION_POINTER_ID_MASK) >> MotionEvent.ACTION_POINTER_ID_SHIFT;
	   		bcRenderer.TouchEvent(event.getPointerId(idx), TOUCH_STOP, (int) event.getX(idx), (int) event.getY(idx));	   		
	        return true;	    
			
		default:
			return super.onTouchEvent(event);
		}
	}

	private static class ContextFactory implements
			GLSurfaceView.EGLContextFactory {
		private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

		public EGLContext createContext(EGL10 egl, EGLDisplay display,
				EGLConfig eglConfig) {
			Log.i(TAG, "creating OpenGL ES 2.0 context");
			checkEglError("Before eglCreateContext", egl);
			int[] attrib_list = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
			EGLContext context = egl.eglCreateContext(display, eglConfig,
					EGL10.EGL_NO_CONTEXT, attrib_list);
			checkEglError("After eglCreateContext", egl);
			return context;
		}

		public void destroyContext(EGL10 egl, EGLDisplay display,
				EGLContext context) {
			egl.eglDestroyContext(display, context);
		}
	}

	private static void checkEglError(String prompt, EGL10 egl) {
		int error;
		while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
			Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
		}
	}

	private static class ConfigChooser implements
			GLSurfaceView.EGLConfigChooser {

		public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
			mRedSize = r;
			mGreenSize = g;
			mBlueSize = b;
			mAlphaSize = a;
			mDepthSize = depth;
			mStencilSize = stencil;
		}

		/*
		 * This EGL config specification is used to specify 2.0 rendering. We
		 * use a minimum size of 4 bits for red/green/blue, but will perform
		 * actual matching in chooseConfig() below.
		 */
		private static int EGL_OPENGL_ES2_BIT = 4;
		private static int[] s_configAttribs2 = { EGL10.EGL_RED_SIZE, 4,
				EGL10.EGL_GREEN_SIZE, 4, EGL10.EGL_BLUE_SIZE, 4,
				EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL10.EGL_NONE };

		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

			/*
			 * Get the number of minimally matching EGL configurations
			 */
			int[] num_config = new int[1];
			egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

			int numConfigs = num_config[0];

			if (numConfigs <= 0) {
				throw new IllegalArgumentException(
						"No configs match configSpec");
			}

			/*
			 * Allocate then read the array of minimally matching EGL configs
			 */
			EGLConfig[] configs = new EGLConfig[numConfigs];
			egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs,
					num_config);

			if (DEBUG) {
				printConfigs(egl, display, configs);
			}
			/*
			 * Now return the "best" one
			 */
			return chooseConfig(egl, display, configs);
		}

		public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
				EGLConfig[] configs) {
			EGLConfig bestConfig = null;
			int lastDepthSize = -1;
			int lastStencilSize = -1;
			for (EGLConfig config : configs) {
				int d = findConfigAttrib(egl, display, config,
						EGL10.EGL_DEPTH_SIZE, 0);
				int s = findConfigAttrib(egl, display, config,
						EGL10.EGL_STENCIL_SIZE, 0);

				// We need at least mDepthSize and mStencilSize bits
				if (d < mDepthSize || s < mStencilSize)
					continue;

				// We want an *exact* match for red/green/blue/alpha
				int r = findConfigAttrib(egl, display, config,
						EGL10.EGL_RED_SIZE, 0);
				int g = findConfigAttrib(egl, display, config,
						EGL10.EGL_GREEN_SIZE, 0);
				int b = findConfigAttrib(egl, display, config,
						EGL10.EGL_BLUE_SIZE, 0);
				int a = findConfigAttrib(egl, display, config,
						EGL10.EGL_ALPHA_SIZE, 0);

				int configId = findConfigAttrib(egl, display, config,
						EGL10.EGL_CONFIG_ID, 0);

				if (r == mRedSize && g == mGreenSize && b == mBlueSize
						&& a == mAlphaSize) {
					Log.i(TAG, String.format("Using configId: %d", configId));
					return config;
				}
			}
			return null;
		}

		private int findConfigAttrib(EGL10 egl, EGLDisplay display,
				EGLConfig config, int attribute, int defaultValue) {

			if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
				return mValue[0];
			}
			return defaultValue;
		}

		private void printConfigs(EGL10 egl, EGLDisplay display,
				EGLConfig[] configs) {
			int numConfigs = configs.length;
			Log.i(TAG, String.format("%d configurations", numConfigs));
			for (int i = 0; i < numConfigs; i++) {
				Log.i(TAG, String.format("Configuration %d:\n", i));
				printConfig(egl, display, configs[i]);
			}
		}

		private void printConfig(EGL10 egl, EGLDisplay display, EGLConfig config) {
			int[] attributes = { EGL10.EGL_BUFFER_SIZE, EGL10.EGL_ALPHA_SIZE,
					EGL10.EGL_BLUE_SIZE,
					EGL10.EGL_GREEN_SIZE,
					EGL10.EGL_RED_SIZE,
					EGL10.EGL_DEPTH_SIZE,
					EGL10.EGL_STENCIL_SIZE,
					EGL10.EGL_CONFIG_CAVEAT,
					EGL10.EGL_CONFIG_ID,
					EGL10.EGL_LEVEL,
					EGL10.EGL_MAX_PBUFFER_HEIGHT,
					EGL10.EGL_MAX_PBUFFER_PIXELS,
					EGL10.EGL_MAX_PBUFFER_WIDTH,
					EGL10.EGL_NATIVE_RENDERABLE,
					EGL10.EGL_NATIVE_VISUAL_ID,
					EGL10.EGL_NATIVE_VISUAL_TYPE,
					0x3030, // EGL10.EGL_PRESERVED_RESOURCES,
					EGL10.EGL_SAMPLES,
					EGL10.EGL_SAMPLE_BUFFERS,
					EGL10.EGL_SURFACE_TYPE,
					EGL10.EGL_TRANSPARENT_TYPE,
					EGL10.EGL_TRANSPARENT_RED_VALUE,
					EGL10.EGL_TRANSPARENT_GREEN_VALUE,
					EGL10.EGL_TRANSPARENT_BLUE_VALUE,
					0x3039, // EGL10.EGL_BIND_TO_TEXTURE_RGB,
					0x303A, // EGL10.EGL_BIND_TO_TEXTURE_RGBA,
					0x303B, // EGL10.EGL_MIN_SWAP_INTERVAL,
					0x303C, // EGL10.EGL_MAX_SWAP_INTERVAL,
					EGL10.EGL_LUMINANCE_SIZE, EGL10.EGL_ALPHA_MASK_SIZE,
					EGL10.EGL_COLOR_BUFFER_TYPE, EGL10.EGL_RENDERABLE_TYPE,
					0x3042 // EGL10.EGL_CONFORMANT
			};
			String[] names = { "EGL_BUFFER_SIZE", "EGL_ALPHA_SIZE",
					"EGL_BLUE_SIZE", "EGL_GREEN_SIZE", "EGL_RED_SIZE",
					"EGL_DEPTH_SIZE", "EGL_STENCIL_SIZE", "EGL_CONFIG_CAVEAT",
					"EGL_CONFIG_ID", "EGL_LEVEL", "EGL_MAX_PBUFFER_HEIGHT",
					"EGL_MAX_PBUFFER_PIXELS", "EGL_MAX_PBUFFER_WIDTH",
					"EGL_NATIVE_RENDERABLE", "EGL_NATIVE_VISUAL_ID",
					"EGL_NATIVE_VISUAL_TYPE", "EGL_PRESERVED_RESOURCES",
					"EGL_SAMPLES", "EGL_SAMPLE_BUFFERS", "EGL_SURFACE_TYPE",
					"EGL_TRANSPARENT_TYPE", "EGL_TRANSPARENT_RED_VALUE",
					"EGL_TRANSPARENT_GREEN_VALUE",
					"EGL_TRANSPARENT_BLUE_VALUE", "EGL_BIND_TO_TEXTURE_RGB",
					"EGL_BIND_TO_TEXTURE_RGBA", "EGL_MIN_SWAP_INTERVAL",
					"EGL_MAX_SWAP_INTERVAL", "EGL_LUMINANCE_SIZE",
					"EGL_ALPHA_MASK_SIZE", "EGL_COLOR_BUFFER_TYPE",
					"EGL_RENDERABLE_TYPE", "EGL_CONFORMANT" };
			int[] value = new int[1];
			for (int i = 0; i < attributes.length; i++) {
				int attribute = attributes[i];
				String name = names[i];
				if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
					Log.i(TAG, String.format("  %s: %d\n", name, value[0]));
				} else {
					// Log.w(TAG, String.format("  %s: failed\n", name));
					while (egl.eglGetError() != EGL10.EGL_SUCCESS)
						;
				}
			}
		}

		// Subclasses can adjust these values:
		protected int mRedSize;
		protected int mGreenSize;
		protected int mBlueSize;
		protected int mAlphaSize;
		protected int mDepthSize;
		protected int mStencilSize;
		private int[] mValue = new int[1];
	}

	private static class Renderer implements GLSurfaceView.Renderer {
		private Callback callback_;

		public void onDrawFrame(GL10 gl) {
			gl.glDisable(GL10.GL_DITHER);
			gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
			if (callback_ != null)
				callback_.LmiDeviceManagerViewRender();
		}

		public void onSurfaceChanged(GL10 gl, int width, int height) {
			Log.i(TAG, "onSurfaceChanged()");
			if (callback_ != null)
				callback_.LmiDeviceManagerViewResize(width, height);
		}

		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			Log.i(TAG, "onSurfaceCreated()");
			gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_FASTEST);
			gl.glShadeModel(GL10.GL_SMOOTH);
			callback_.LmiDeviceManagerViewRenderRelease();
		}

		public void TouchEvent(int id, int type, int x, int y) {
			callback_.LmiDeviceManagerViewTouchEvent(id, type, x, y);
		}

		public void SetCallback(Callback callback) {
			callback_ = callback;
		}
	}
}
