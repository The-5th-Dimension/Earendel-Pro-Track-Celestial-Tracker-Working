import json

# Replace 'data.json' with the name of your JSON file
with open('data.json', 'r') as file:
    data = json.load(file)

filtered_data = [{"hd": item["hd"], "ra": item["ra"], "dec": item["dec"]} for item in data]

# Replace 'filtered_data.json' with the name of the output JSON file
with open('filtered_data.json', 'w') as file:
    json.dump(filtered_data, file)