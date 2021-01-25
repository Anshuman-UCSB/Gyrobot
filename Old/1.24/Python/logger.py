import requests
class Logger:
    def __init__(self, ip):
        self.ip = ip

    def post(self, x, y):
        requests.post("http://192.168.0.34:5000/", data = f"{x},{y}")

    def delete(self):
        requests.delete("http://192.168.0.34:5000/")