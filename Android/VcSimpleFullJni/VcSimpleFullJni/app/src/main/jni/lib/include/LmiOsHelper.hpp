//
// LmiOsHelper.hpp
//
// helper classes for LmiOS functions
// Copyright 2010 Vidyo Inc. All rights reserved.
//


#ifndef __LmiOsHelper_hpp__
#define __LmiOsHelper_hpp__

#if !defined(__cplusplus)
//cause compilation error in c files
	int Error__This_Header_File_Should_Only_Be_included_in_CPlusPlus_Files[-1];
#endif

#include <Lmi/Os/LmiMutex.h>

// Self destructing mutex class
class CLmiMutex
{
 	LmiMutex m_mutex;
 	bool m_isValid;
public:
			CLmiMutex()	{	m_isValid = (LmiMutexConstruct(&m_mutex) !=NULL); }
	virtual ~CLmiMutex(){	LmiMutexDestruct(&m_mutex);	}
	void 	lock()		{	LmiMutexLock(&m_mutex);		} 
	void 	unlock()	{	LmiMutexUnlock(&m_mutex);	} 
	bool 	isValid()	{	return m_isValid;			}
};

class CMutexLocker
{
	CLmiMutex&	m_mutex;
public:
	CMutexLocker(CLmiMutex&	mutex): m_mutex(mutex) { m_mutex.lock(); }
	~CMutexLocker()	{ m_mutex.unlock(); }
  private:  // CMutexLocker is non copyable
      CMutexLocker( const CMutexLocker& m):m_mutex(m.m_mutex){}
      const CMutexLocker& operator=( const CMutexLocker& m){}
};


#include <Lmi/Os/LmiTimer.h>
#include <Lmi/Transport/LmiSocketTimerLoop.h>
#include <Lmi/AppFramework/LmiAppParticipant.h>

// simple to use LmiTimer class

template <class Func,typename Data = void*>
class CLmiTimer
{

LmiTimer m_timer;
Func m_expireyFunctor;
Data m_payload;
bool m_isValid;
double m_numofSeconds;

	inline LmiTime nano_(double numofSeconds) {return static_cast<LmiTime>(LMI_NSECS_PER_SEC * numofSeconds); }
	
public:
	CLmiTimer(Func Functor, Data  Payload, double numofSeconds, LmiTimerManager* tm):
		m_expireyFunctor(Functor),
		m_payload(Payload),
		m_numofSeconds(numofSeconds),
		m_isValid(false)
	{	
		if(NULL != tm)
		{
			if(NULL !=  LmiTimerConstruct(&m_timer, CLmiTimer::TimerExpiryCallback, (LmiVoidPtr)this, tm) )
			{
				m_isValid = LMI_TRUE;
			}
		}
	}
	
	virtual ~CLmiTimer()
	{
		LmiTimerDestruct(&m_timer);  
		m_isValid = false;
	}
	
	const Data& payload() const { return m_payload; }
	bool isValid() const {	return m_isValid;		}
	bool stop() {  return (LMI_TRUE == LmiTimerStop(&m_timer)); }
	bool isInTimerCallback(){  return (LMI_TRUE == LmiTimerIsInTimerCallback(&m_timer)); }
	bool start() {  return (m_isValid = (LMI_TRUE == LmiTimerStart(&m_timer,nano_(m_numofSeconds)))); }
	bool pending() {  return (LMI_TRUE == LmiTimerPending(&m_timer)); }

private:

	void nonStaticTimerExpiryCallback()
	{
		m_expireyFunctor(m_payload); //call expirey data with payload
	}	
	
	static void TimerExpiryCallback(LmiTimer* timer, LmiVoidPtr userData)
	{
		CLmiTimer* that = (CLmiTimer*) userData; //extract "this" pointer
		if (that->m_isValid)
			that->nonStaticTimerExpiryCallback(); //call expirey data with payload
	}	

};


inline LmiTimerManager *LmiAppParticipantGetSocketTimerTimerManager()
{
	 LmiSocketTimerLoop *socketTimerLoop = LmiAppParticipantGetSocketTimerLoop();
	if(socketTimerLoop)
	{
		return LmiSocketTimerLoopGetTimerManager(socketTimerLoop);
	}
	return NULL;		
}

#endif // __LmiOsHelper_hpp__
