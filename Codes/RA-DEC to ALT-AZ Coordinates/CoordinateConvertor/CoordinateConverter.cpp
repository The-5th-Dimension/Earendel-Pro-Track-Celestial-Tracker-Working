#include <cmath>
#include <vector>

#include "CoordinateConverter.h"

using namespace std;

CoordinateConverter::CoordinateConverter()
{
}

CoordinateConverter::CoordinateConverter(double lat, double longi)
{
    latitude = lat;
    longitude = longi;
}

void CoordinateConverter::updateLocation(double lat, double longi)
{
    latitude = lat;
    longitude = longi;
}

void CoordinateConverter::updateDateUTC(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void CoordinateConverter::updateTimeUTC(int h, int min, double sec)
{
    hour = h;
    minute = min;
    second = sec;
}

double CoordinateConverter::convert_60_60(int hours, int minutes, int seconds, bool negative)
{
    double magnitude = hours + (minutes / 60.0) + (seconds / 3600.0);
    double signed_magnitude = pow(-1, int(negative)) * magnitude;

    return signed_magnitude;
}

void CoordinateConverter::update_RA_DEC(double right_ascension, double declination)
{
    ra = right_ascension;
    dec = declination;
}

void CoordinateConverter::update_RA_DEC(int ra_h, int ra_min, float ra_sec, bool ra_neg, int dec_deg, int dec_arcmin, float dec_arcsec, bool dec_neg)
{
    double right_ascension = convert_60_60(ra_h, ra_min, ra_sec, ra_neg);
    double declination = convert_60_60(dec_deg, dec_arcmin, dec_arcsec, dec_neg);

    update_RA_DEC(right_ascension, declination);
}

long int CoordinateConverter::julianDate()
{
    int years = year - 2000;
    int leap_years = 0;

    for (int i = 2000; i < year; i++)
    {
        if (i % 4 == 0)
            leap_years++;
    }

    long int days1 = (leap_years * 366) + ((years - leap_years) * 365);

    int m_days[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int m_days_leap[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

    int days2 = (year % 4 == 0) ? m_days_leap[month - 1] : m_days[month - 1];

    long int days = days1 + days2 + (day - 1);

    julianDate_ = days;

    return julianDate_;
}

double CoordinateConverter::julianTime()
{
    long int jdate = julianDate();

    double hours = hour + (minute / 60.0) + (second / 3600.0);

    if (hour > 12)
        hours -= 12;

    double jtime = jdate + (hours / 24.0);

    julianTime_ = jtime;

    return julianTime_;
}

double CoordinateConverter::gmst()
{
    double d = julianTime();

    double value = 100.46 + (0.985647 * d) + (15 * convert_60_60(hour, minute, second, false));

    value = fmod(value, 360);

    if (value < 0)
        value += 360;

    gmst_ = value * 24.0 / 360.0;

    return gmst_;
}

double CoordinateConverter::lmst()
{
    gmst();
    double lambda_h = longitude / 360.0 * 24;
    lmst_ = fmod(gmst_ + lambda_h, 24);

    return lmst_;
}

double CoordinateConverter::hourAngle()
{
    double lst = lmst();
    double temp = lst - ra;

    if (temp < 0)
        temp += 24;

    ha_ = temp;

    return ha_;
}

vector<double> CoordinateConverter::RADEC_to_ALTAZ()
{
    double ha = hourAngle();   // hours
    ha = ha * 2 * M_PI / 24.0; // radians

    double latitude_ = latitude * (M_PI / 180.0); // degrees to radians

    double ra_ = ra * (2 * M_PI / 24.0); // hours to radians
    double dec_ = dec * (M_PI / 180.0);  // degrees to radians

    double altitude_ = asin(sin(dec_) * sin(latitude_) + cos(dec_) * cos(latitude_) * cos(ha)); // radians

    double azimuth_ = acos((sin(dec_) - sin(altitude_) * sin(latitude_)) / (cos(altitude_) * cos(latitude_))); // radians

    if (sin(ha) >= 0)
        azimuth_ = 2 * M_PI - azimuth_;

    altitude = altitude_ * (180 / M_PI);
    azimuth = azimuth_ * (180 / M_PI);

    vector<double> altaz = {altitude, azimuth};

    return altaz;
}

vector<double> CoordinateConverter::convert()
{
    return RADEC_to_ALTAZ();
}

vector<double> CoordinateConverter::convert(double right_ascension, double declination)
{
    update_RA_DEC(right_ascension, declination);
    return RADEC_to_ALTAZ();
}

vector<double> CoordinateConverter::convert(int ra_h, int ra_min, float ra_sec, bool ra_neg, int dec_deg, int dec_arcmin, float dec_arcsec, bool dec_neg)
{
    update_RA_DEC(ra_h, ra_min, ra_sec, ra_neg, dec_deg, dec_arcmin, dec_arcsec, dec_neg);
    return RADEC_to_ALTAZ();
}