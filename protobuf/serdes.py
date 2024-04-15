import format_pb2

store = format_pb2.data()

with open("store_dump", "rb") as f:
    store.ParseFromString(f.read())

for key, entry in store.map.items():
    print(f"key : {key}  value: {entry.value} expiry :{entry.expiry}")

# Output:
#key : job  value: SDE expiry :1
#key : surname  value: Kishan expiry :1000
#key : name  value: Ram expiry :1000