import requests
from datetime import datetime
from lxml import etree
import re

def get_metar_info(icao):
    api_url = f"https://www.aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=xml&stationString={icao}&hoursBeforeNow=2"

    response = requests.get(api_url)

    # Remove the Unicode encoding declaration from the XML data
    xml_data = response.text.replace('<?xml version="1.0" encoding="UTF-8"?>', '')

    # Parse the XML data
    root = etree.fromstring(xml_data)

    # Find the METAR element and extract its raw_text
    data = root.find("data")
    metar = data.find("METAR")
    raw_text = metar.find("raw_text").text

    return raw_text

""" def decode_metar_info(metar_raw):

    # Define the regular expression pattern
    pattern = re.compile(r"(?P<station_id>\w+)\s+(?P<time_str>\d{6}Z)\s+(AUTO)?\s+(?P<wind_dir>\d{3}|VRB)(?P<wind_speed>\d{2,3})(G(?P<wind_gust>\d{2,3}))?(?P<wind_unit>KT)?\s+"
                         r"(?P<vis_dist>(?:\d{1,3}|M)?(?:\.\d{1,2})?)(?P<vis_unit>SM)?\s+(?P<sky_cond>VV|SKC|CLR|FEW|SCT|BKN|OVC)(?P<cloud_height>\d{3})?\s+"
                         r"(?P<temp_str>M?\d{2})/(?P<dew_str>M?\d{2})\s+(?P<pressure_str>A\d{4})\s+(?P<remarks>.*)", re.DOTALL)

    # Match the pattern against the raw METAR string
    match = re.match(pattern, metar_raw)

    # Check if a match was found
    if match:
        # Extract the decoded METAR information from the match
        metar_info = match.groupdict()

        # Return the decoded METAR information
        return metar_info
    else:
        # Return None if no match was found
        return None """

def decode_metar_info(metar_raw):
    # Define the regular expression pattern
    pattern = re.compile(r"(?P<station_id>\w{4})\s+(?P<time_str>\d{6}Z)\s+(?P<auto>AUTO)?\s+(?P<wind_dir>\d{3}|VRB)(?P<wind_speed>\d{2,3})(G(?P<wind_gust>\d{2,3}))?(?P<wind_unit>KT)?\s+"
                     r"(?P<vis_dist>(?:\d{1,3}|M)?(?:\.\d{1,2})?)(?P<vis_unit>SM)?\s+(?P<sky_cond>(VV|SKC|CLR|FEW|SCT|BKN|OVC|CAVOK))(?P<cloud_height>\d{3})?( (?P<weather_event>-RA|-SN|-TS|-GR|-GS|-BR|-FG|-FU|-DZ|-VA|-SA|-HZ|-PY|-PO|-SQ|-FC|-SS|-DS|-TSRA|-SHRA|-GS|-SHGS|-SHGR|-SHPE|-TSGS|-TSGR|-TSRA))*\s+"
        r"(?P<temp_str>M?\d{2})/(?P<dew_str>M?\d{2})\s+(?P<pressure_str>A\d{4})\s+(?P<additional_info>(\w+ \d+ \w+ \d+))?\s+(?P<remarks>(?:[A-Z]{2}[\d]{3})?(?:[A-Z]+\s[\d]{4})*)$", re.DOTALL
        )


    # Match the pattern against the raw METAR string
    match = re.match(pattern, metar_raw)

    # Check if a match was found
    if match:
        # Extract the decoded METAR information from the match
        metar_info = match.groupdict()
        # Check if the pressure string contains "A" at the beginning, which indicates that the pressure is in inches of mercury
        if metar_info['pressure_str'].startswith('A'):
            # If the pressure is in inches of mercury, remove the "A" at the beginning of the string and add "inHg" as the unit
            metar_info['pressure_str'] = metar_info['pressure_str'][1:] + 'inHg'
        else:
            # If the pressure is not in inches of mercury, add "hPa" as the unit
            metar_info['pressure_str'] = metar_info['pressure_str'] + 'hPa'

        # Return the decoded METAR information
        return metar_info
    else:
        # Return None if no match was found
        return None

def print_metar_info(metar_raw):
    # Decode the METAR information
    decoded_metar = decode_metar_info(metar_raw)

    # Check if the decoded METAR information is not None
    if decoded_metar:
        # Print the station identifier
        print(f"Station: {decoded_metar['station_id']}")

        # Print the observation time
        print(f"Observation time: {decoded_metar['time_str']}")

        # Print the wind information
        print("Wind:")
        print(f"\tDirection: {decoded_metar['wind_dir']} degrees")
        print(f"\tSpeed: {decoded_metar['wind_speed']} knots")
        if decoded_metar['wind_gust']:
            print(f"\tGust: {decoded_metar['wind_gust']} knots")

        # Print the visibility information
        print("Visibility:")
        print(f"\tDistance: {decoded_metar['vis_dist']} meters")
        if decoded_metar['vis_unit']:
            print(f"\tUnit: {decoded_metar['vis_unit']}")

        # Print the sky conditions
        print("Sky conditions:")
        print(f"\t{decoded_metar['sky_cond']}")
        if decoded_metar['cloud_height']:
            print(f"\tHeight: {decoded_metar['cloud_height']} feet")

        # Print the temperature and dew point
        print("Temperature and dew point:")
        print(f"\tTemperature: {decoded_metar['temp_str']} degrees Celsius")
        print(f"\tDew point: {decoded_metar['dew_str']} degrees Celsius")

        # Print the pressure
        print(f"Pressure: {decoded_metar['pressure_str']}")

        # Print the additional info
        additional_info = decoded_metar.get('additional_info')
        if additional_info:
            print(f"Additional info: {additional_info}")

        # Print the remarks
        remarks = decoded_metar.get('remarks')
        if remarks:
            print(f"Remarks: {remarks}")
    else:
        print("Unable to decode METAR")

if __name__ == "__main__":
    icao = input("Enter the airport ICAO code: ")
    metar_info = get_metar_info(icao)
    print(f"The METAR information at {icao} airport is: {metar_info}")
    print_metar_info(metar_info)
    """decoded_metar = decode_metar_info(metar_info)
    print(decoded_metar)"""

