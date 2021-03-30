import requests
  
# defining the api-endpoint 
API_ENDPOINT = "https://ec2-65-0-71-89.ap-south-1.compute.amazonaws.com:8443"


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
