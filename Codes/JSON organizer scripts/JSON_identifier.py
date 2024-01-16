import json

with open('filtered_data.json') as f:
    data = json.load(f)

# Use the 'hd' key as the identifier
result = {item['hd']: {'ra': item['ra'], 'dec': item['dec']} for item in data if item['hd']}

with open('output.json', 'w') as f:
    json.dump(result, f, indent=2)