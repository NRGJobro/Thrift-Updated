#include "TimeUtils.h"
#include "Utils.h"

float prevMS = 0.f;

bool TimeUtils::hasTimeElapsed(float sec) {
	if (getTime() - prevMS >= (sec)) {
		reset();
		return true;
	}
	return false;
};

void TimeUtils::reset() {
	prevMS = getTime();
};

unsigned __int64 TimeUtils::getCurrentMs() {

	FILETIME f;
	GetSystemTimeAsFileTime(&f);
	(long long)f.dwHighDateTime;
	unsigned __int64 nano = ((__int64)f.dwHighDateTime << 32LL) + (__int64)f.dwLowDateTime;
	return (nano - 116444736000000000LL) / 10000;
};

float TimeUtils::getTime() {
	std::chrono::high_resolution_clock m_clock;
	return std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count() / 1000000.f;
};