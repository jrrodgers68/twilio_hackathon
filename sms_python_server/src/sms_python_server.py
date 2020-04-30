from flask import Flask, request, redirect
from twilio.twiml.messaging_response import MessagingResponse
import requests
import os

app = Flask(__name__)

known_commands = {
    "forward": "f",
    "f": "f",
    "backward": "b",
    "b":"b",
    "left": "l",
    "l": "l",
    "right": "r",
    "r": "r",
    "dance": "d",
    "d": "d",
    "nerd dance": "n",
    "nerd": "n",
    "n": "n"
}


def find_sparki_command(dict, key):
    # try to look up the key in the dictionary
    # if found, return the value
    # otherwise, grab the first character of the key
    #  and look that up
    # return None if nothing found
    if key in dict.keys():
        return dict[key]
    else:
        k = key[:1]
        if k in dict.keys():
            return dict[k]
        else:
            return None


def send_command_to_Sparki(command):
    particle_access_token = os.environ.get("PARTICLE_ACCESS_TOKEN")
    device_id = os.environ.get("DEVICE_ID")
    api = f"https://api.particle.io/v1/devices/{device_id}/sparki"
    data = {
        'access_token':particle_access_token,
        'arg':command
    }
    print(f"sending request to {api} with this payload:{data}")
    r = requests.post(url = api, data = data)
    print(f"response was {r}")


def handle_request(command):
    # split the text received into components delimited by spaces
    #  each component should be a specific command that sparki will
    #  execute.  Need to validate the commands against our known list
    #  and only allow those into the resulting command we send to the
    #  Particle Argon that servers as Sparki's internet link
    sparki_commands = []
    components = command.split()
    for i in components:
        sc = find_sparki_command(known_commands, i.lower())
        if(sc is not None):
            sparki_commands.append(sc)
    # Sparki is a hard working robot, no need to overtax him!
    SPARKI_COMMAND_LIMIT = 30
    if(len(sparki_commands) > SPARKI_COMMAND_LIMIT):
        sparki_commands = sparki_commands[:SPARKI_COMMAND_LIMIT]
    string_commands = ''.join(sparki_commands)
    string_commands += '\n'  # Sparki is using a new line as an end of command indicator
    send_command_to_Sparki(string_commands)


@app.route('/sparki', methods=['POST'])
def command():
    body = request.values.get('Body', None)
    result = handle_request(body)
    resp = MessagingResponse()
    resp.message(result)
    return str(resp)


if __name__ == "__main__":
    app.run(port=5000)
