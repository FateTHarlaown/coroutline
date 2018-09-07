//
// Created by NorSnow_ZJ on 2018/8/23.
//

#include "channel.h"
#include "poller.h"

int Channel::getEvents()
{
    return events_;
}

int Channel::getRevents()
{
    return revents_;
}

void Channel::setRevents(int revents)
{
    revents_ = revents;
}

void Channel::enableWirte()
{
    events_ |= kWriteEvent;
}

void Channel::enableRead()
{
    events_ |= kReadEvent;
}

void Channel::disableWrite()
{
    events_ &= ~kWriteEvent;
}

void Channel::disableRead()
{
    events_ &= ~kReadEvent;
}

void Channel::clearEvents()
{
    events_ = kNoEvent;
}

void Channel::clearCallbacks()
{
    readCallbackFunc_ = nullptr;
    writeCallbackFunc_ = nullptr;
    errorCallbackFunc_ = nullptr;
}

void Channel::setReadCallbackFunc(EventCallbackFunc func)
{
    readCallbackFunc_ = func;
}

void Channel::setWriteCallbackFunc(EventCallbackFunc func)
{
    writeCallbackFunc_ = func;
}

void Channel::setErrorCallbackFunc(EventCallbackFunc func)
{
    errorCallbackFunc_ = func;
}

int Channel::getFd()
{
    return fd_;
}

void Channel::addToPoller()
{
    poller_->addChannel(this);
}

void Channel::removeFromPoller()
{
    poller_->removeChannel(this);
}

void  Channel::handleEvents()
{
    if (revents_ & kWriteEvent) {
        if (writeCallbackFunc_) {
            writeCallbackFunc_();
        }
    }

    if (revents_ & kReadEvent) {
        if (readCallbackFunc_) {
            readCallbackFunc_();
        }
    }

    if (revents_ & kErrorEvent) {
        if (errorCallbackFunc_) {
            errorCallbackFunc_();
        }
    }

}