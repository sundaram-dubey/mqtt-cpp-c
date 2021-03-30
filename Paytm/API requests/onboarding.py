import requests
  
# defining the api-endpoint 
API_ENDPOINT = "https://ec2-65-0-71-89.ap-south-1.compute.amazonaws.com:8443"

on_boarding_data = {
	  "deviceId": "string",
	  "type": "string"
	}
  
# sending post request and saving response as response object
r = requests.post(url = API_ENDPOINT + "/iot/onboard", data = on_boarding_data)
print(r)
# extracting response text 
x = r.text

authId = x['authId']
certificatePem = x['certificatePem']
privateKey = x['privateKey']
rootCertificate = x['rootCertificate']
