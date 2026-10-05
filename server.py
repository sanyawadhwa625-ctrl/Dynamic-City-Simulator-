from http.server import HTTPServer, BaseHTTPRequestHandler
import subprocess
import json

HOST = "127.0.0.1"
PORT = 5000


class NovaCityServer(BaseHTTPRequestHandler):

    def send_json(self, data):

        response = json.dumps(data).encode("utf-8")

        self.send_response(200)
        self.send_header("Content-Type", "application/json")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header(
            "Access-Control-Allow-Methods",
            "GET, POST, OPTIONS"
        )
        self.send_header(
            "Access-Control-Allow-Headers",
            "Content-Type"
        )
        self.end_headers()

        self.wfile.write(response)


    def do_OPTIONS(self):

        self.send_response(200)
        self.send_header(
            "Access-Control-Allow-Origin",
            "*"
        )
        self.send_header(
            "Access-Control-Allow-Methods",
            "GET, POST, OPTIONS"
        )
        self.send_header(
            "Access-Control-Allow-Headers",
            "Content-Type"
        )
        self.end_headers()


    def do_GET(self):

        if self.path == "/":

            self.send_json({
                "status": "online",
                "message": "Nova City C Backend Bridge is running"
            })

            return


        if self.path.startswith("/city"):

            command = "demo"

            if "?" in self.path:

                query = self.path.split("?", 1)[1]

                if query.startswith("command="):

                    command = query.split("=", 1)[1]


            self.run_backend(command)

            return


        self.send_json({
            "status": "error",
            "message": "Unknown endpoint"
        })


    def run_backend(self, command):

        try:

            result = subprocess.run(
                ["backend.exe", command],
                capture_output=True,
                text=True,
                shell=True
            )

            self.send_json({
                "status": "success",
                "output": result.stdout
            })


        except Exception as error:

            self.send_json({
                "status": "error",
                "message": str(error)
            })


print("============================================")
print("        NOVA CITY PYTHON BRIDGE")
print("============================================")
print()
print("Server running at:")
print("http://127.0.0.1:5000")
print()
print("Keep this terminal open.")
print("============================================")


server = HTTPServer((HOST, PORT), NovaCityServer)
server.serve_forever()