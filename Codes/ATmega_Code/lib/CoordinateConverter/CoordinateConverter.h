#include <cmath>
#include <vector>

using namespace std;

class CoordinateConverter
{
private:
    double latitude = 0, longitude = 0;
    int year = 2020, month = 1, day = 1;
    int hour = 12, minute = 0;
    float second = 0;

    long int julianDate_ = 0;
    double julianTime_ = 0, gmst_ = 0, lmst_ = 0, ha_ = 0;
    double ra = 0, dec = 0;

    double altitude = 0, azimuth = 0;

    double convert_60_60(int hours, int minutes, int seconds, bool negative);
    long int julianDate();
    double julianTime();
    double gmst();
    double lmst();
    double hourAngle();
    vector<double> RADEC_to_ALTAZ();

public:
    CoordinateConverter();
    CoordinateConverter(double lat, double longi);
    void updateLocation(double lat, double longi);
    void updateDateUTC(int d, int m, int y);
    void updateTimeUTC(int h, int min, double sec);
    void update_RA_DEC(double right_ascension, double declination);
    void update_RA_DEC(int ra_h, int ra_min, float ra_sec, bool ra_neg, int dec_deg, int dec_arcmin, float dec_arcsec, bool dec_neg);
    vector<double> convert();
    vector<double> convert(double right_ascension, double declination);
    vector<double> convert(int ra_h, int ra_min, float ra_sec, bool ra_neg, int dec_deg, int dec_arcmin, float dec_arcsec, bool dec_neg);
};