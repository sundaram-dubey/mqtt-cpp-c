import requests

response = requests.post('https://iot-dev.paytm.in/download/unbind.wav?name=paytm', headers={"Auth-Token":"f23992229db875e41fa7e28c55da1651f864ac7f495d913a5af5aabd659c72a1"})

with open('output.wav', 'wb') as f:
	f.write(response.content)
	