import datetime
def addTimePaused(startTime, pausedTime):
    return (startTime + (datetime.datetime.now() - pausedTime))

def currentTime():
    return datetime.datetime.now()

def secondspent(start,finish):
    return (finish-start).total_seconds()

