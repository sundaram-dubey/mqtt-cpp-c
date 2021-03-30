import requests
  
# defining the api-endpoint 
API_ENDPOINT = "https://ec2-65-0-71-89.ap-south-1.compute.amazonaws.com:8443"

# add device

add_device_data = {
  "model": "string",
  "os": "string",
  "type": "string",
  "vendorName": "string"
}

r = requests.post(url = API_ENDPOINT + "/iot/add_device", data = add_device_data)
# extracting response text 
response_voice_text = r.text
#response to be said when the device is added



# data to be sent to api for onboarding
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

##Transaction Notification
transaction_notification_data = {
	  "acquirementId": "string",
	  "authId": "string",
	  "deviceId": "string",
	  "deviceType": "string",
	  "merchantId": "string",
	  "merchantTransId": "string",
	  "orderAmount": 0,
	  "orderStatus": "string",
	  "secondaryId": "string"
	}


r = requests.post(url = API_ENDPOINT + "/iot/transaction_notification", data = white_listing_data)
print(r)
x = r.text

amount = x['amount'] ##amount of transfer
command = x['command']  ##mode of transfer I guess
merchantTransId = x['merchantTransId']
status = x['status']

transaction_voice_message = "payments of Rs" + str(amount)

last_transaction_data = {
	  "command": "string",
	  "deviceId": "string",
	  "deviceType": "string",
	  "requestId": "string"
	}

r = requests.post(url = API_ENDPOINT + "/iot/last_transaction", data = white_listing_data)
print(r)
x = r.text


last_transaction_amount = x['amount']
command = x['command']
last_transaction_requestId = x['requestId']


