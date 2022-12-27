import requests
from lxml import etree

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


if __name__ == "__main__":
    icao = input("Enter the airport ICAO code: ")
    metar_info = get_metar_info(icao)
    print(f"The METAR information at {icao} airport is: {metar_info}")


