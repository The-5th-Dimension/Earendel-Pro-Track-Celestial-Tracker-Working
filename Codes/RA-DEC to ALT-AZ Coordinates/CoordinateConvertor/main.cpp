#include <iostream>
#include <cmath>
#include <vector>

#include "CoordinateConverter.h"

int main()
{
    // Location is added as latitude and longitude respectively, in the constructor.
    // East and North values are positive, while West and South values are negative.
    CoordinateConverter converter(7.4818, 80.3609); // Kurunegala, Sri Lanka

    // Date should be the UTC date. (i.e.: Date of England.)
    // Local date cannot be used since the calculations need the UTC date.
    // Convert the local date to UTC date externally, before updating.
    // Date is added in the dd.mm.yyyy format.
    converter.updateDateUTC(9, 1, 2024);

    // Time should be the UTC time. (i.e.: Time in Greenwich, England.)
    // Local time cannot be used since it has a discrete format due to time zones.
    // Convert the local time to UTC time externally, before updating.
    // Time is added in the 24-h: min: sec format.
    converter.updateTimeUTC(6, 23, 51.8932);

    // Add the Right Ascension (RA) and Declination (DEC) coordinates.
    // Alternative formats are as follows.
    // void update_RA_DEC(int ra_h, int ra_min, float ra_sec, bool ra_neg, int dec_deg, int dec_arcmin, float dec_arcsec, bool dec_neg);
    // void update_RA_DEC(double right_ascension, double declination);

    // Use the convert(...) function to convert the RA-DEC coordinates to ALT_AZ coordinates.
    // Returns a vector of two elements, Altitude and Azimuth respectively.
    vector<double> alt_az = converter.convert(6, 45, 9, false, 16, 48, 52, true); // RA-DEC coordinates of Sirius
    // Note that boolean values indicate whether the whole quantity is negative or positive.

    // Print the obtained altitude, and azimuth.
    cout << "Sirius:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    // More examples.
    // The Sun
    alt_az = converter.convert(19, 17, 1, false, 22, 15, 31, true);
    cout << "The Sun:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    // Jupiter
    alt_az = converter.convert(2, 13, 50, false, 12, 13, 30, false);
    cout << "Jupiter:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    // Polaris
    alt_az = converter.convert(2, 31, 49, false, 89, 15, 51, false);
    cout << "Polaris:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    return 0;
}