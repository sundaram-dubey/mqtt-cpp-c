import requests
  
# defining the api-endpoint 
API_ENDPOINT = "https://ec2-65-0-71-89.ap-south-1.compute.amazonaws.com:8443"


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
