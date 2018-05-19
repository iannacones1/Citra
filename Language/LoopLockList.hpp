#ifndef _LOOP_LOCK_LIST_HPP_
#define _LOOP_LOCK_LIST_HPP_

#include <list>
#include <mutex>
#include <memory>

namespace Citra { namespace Language {

template<class T>
class LoopLockList
{
    public:
        class LoopLock
        {
            public:
        	    LoopLock(std::mutex& inMutex, std::list<T>& inList)
        	     : mLock(inMutex),
        	       mListRef(inList),
        	       mIter(mListRef.begin())
        	    { }

        	    virtual ~LoopLock() { }

        	    void next()
        	    {
        	    	mIter++;
        	    }

        	    const int& data()
        	    {
        	    	return *mIter;
        	    }

        	    bool end()
        	    {
        		    return !(mIter != mListRef.end());
        	    }

            private:
        	    std::lock_guard<std::mutex> mLock;
        	    std::list<T>& mListRef;
        	    typename std::list<T>::iterator mIter;
        };

        std::unique_ptr<LoopLock> getLock()
        {
            return std::unique_ptr<LoopLock>(new LoopLock(mMutex, mData));
        }

        void push_back(const int& inData)
        {
        	std::lock_guard<std::mutex> aLock(mMutex);
        	mData.push_back(inData);
        }

    private:
        std::mutex mMutex;
        std::list<T> mData;
};


} /* namespace Language*/ } /* namespace Citra */

#endif /* _LOOP_LOCK_LIST_HPP_ */
