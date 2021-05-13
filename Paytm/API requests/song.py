import requests

response = requests.post('URI', headers={"Auth-Token":"token"})

with open('output.wav', 'wb') as f:
	f.write(response.content)
	
