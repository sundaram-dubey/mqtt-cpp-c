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

print(response_voice_text)

