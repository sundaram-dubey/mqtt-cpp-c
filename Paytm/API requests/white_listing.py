import requests
  
# defining the api-endpoint 
API_ENDPOINT = "https://ec2-65-0-71-89.ap-south-1.compute.amazonaws.com:8443"


# data to be sent to api for whitelisting..
white_listing_data = {
	  "activationTime": 0,
	  "authId": "string",
	  "deviceId": "string",
	  "deviceLanguage": "string",
	  "deviceModel": "string",
	  "deviceType": "string",
	  "firmwareVersion": "string",
	  "os": "string",
	  "ramSize": 0,
	  "romSize": 0,
	  "serialNo": "string",
	  "vendorName": "string"
	}
  
# sending post request and saving response as response object
r = requests.post(url = API_ENDPOINT + "/iot/whitelist", data = white_listing_data)
print(r)
# extracting response text 
x = r.text

deviceId = x['deviceId']
secretKey = x['secretKey']
deviceType = x['type']
