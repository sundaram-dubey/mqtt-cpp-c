import requests

response = requests.post('uri', headers={"Auth-Token":""})

with open('output.wav', 'wb') as f:
	f.write(response.content)
	
