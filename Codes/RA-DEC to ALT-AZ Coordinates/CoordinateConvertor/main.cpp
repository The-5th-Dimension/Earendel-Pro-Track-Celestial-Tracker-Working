#include <iostream>
#include <cmath>
#include <vector>

#include "CoordinateConvertor.h"

int main()
{
    CoordinateConverter convertor;
    // Location is added as latitude and longitude respectively.
    // East and North values are positive, while West and South values are negative.
    convertor.addLocation(7.4818, 80.3609); // Kurunegala, Sri Lanka

    // Date is added in the dd.mm.yyyy format.
    convertor.updateDate(9, 1, 2024);

    // Time should be the UTC time. (i.e.: Time in Greenwich, England.)
    // Local time cannot be used since it has a discrete format due to time zones.
    // Convert the local time to UTC time externally, before updating.
    // Time is added in the 24-h: min: sec format.
    convertor.updateTimeUTC(6, 23, 51.8932);

    // Add the Right Ascension (RA) and Declination (DEC) coordinates.
    // Format is as follows.
    // void update_RA_DEC(int ra_h, int ra_min, float ra_sec, bool ra_neg, int dec_deg, int dec_arcmin, float dec_arcsec, bool dec_neg)
    // Note that boolean values indicate whether the whole quantity is negative or positive.
    convertor.update_RA_DEC(6, 45, 9, false, 16, 48, 52, true); // RA-DEC coordinates of Sirius
    // Alternatively, void update_RA_DEC(double right_ascension, double declination) format can be used.

    // Use the convert() function to convert the RA-DEC coordinates to ALT_AZ coordinates.
    // Returns a vector of two elements, Altitude and Azimuth respectively.
    vector<double> alt_az = convertor.convert();

    // Print the obtained altitude, and azimuth.
    cout << "Sirius:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    // More examples.
    // The Sun
    convertor.update_RA_DEC(19, 17, 1, false, 22, 15, 31, true);
    alt_az = convertor.convert();
    cout << "The Sun:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    // Jupiter
    convertor.update_RA_DEC(2, 13, 50, false, 12, 13, 30, false);
    alt_az = convertor.convert();
    cout << "Jupiter:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    // Polaris
    convertor.update_RA_DEC(2, 31, 49, false, 89, 15, 51, false);
    alt_az = convertor.convert();
    cout << "Polaris:" << endl;
    cout << "\tAltitude: " << alt_az.at(0) << endl;
    cout << "\tAzimuth: " << alt_az.at(1) << endl;

    return 0;
}