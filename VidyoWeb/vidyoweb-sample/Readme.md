VidyoWeb-Detailed-Sample - version 1.0.0
========================================

A sample app for VidyoWeb developers.

Setup
-----

OSX setup 

Install gulp
	
	npm install --global gulp-cli

Install gulp dependencies
	
	npm install

(Some of these commands might be needed to be run as Admin --> `sudo`)

Windows Setup

Install gitBash

Navigate to the project folder

Install gulp
	
	npm install --global gulp-cli

Install gulp dependencies
	
	npm install


Gulp
-------

Gulp is a javascript task runner that lets the developer automate tasks.
Some tasks

	gulp develop => running on https://localhost:8000/app/index.html
    gulp package
    
It is possible to change the default port for the server - you will need to edit gulpfile.js located at the project root folder:
    gulp.task('develop', function() {
	return gulp.src('./app/')
		.pipe(webserver({
            port:<YOUR PORT>,
			livereload: true,
			directoryListing: true,
			fallback: './index.html',
			https: true
		})
	);
});

