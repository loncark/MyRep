import json
import random

class Picture:
    def __init__(self, id, handle, description, resource, lat, lng):
        self.id = id
        self.handle = handle
        self.description = description
        self.resource = resource
        self.lat = lat
        self.lng = lng

dummyPictures = [
    Picture(1,"blue", "I had a lovely day today, yall. Hopefully tomorrow is as good.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue1.jpg?alt=media&token=daf99baa-4d7a-4d79-b965-35fec2ef5b4c",  40.758105, -73.702477),
    Picture(2,"blue", "Once upon a time there was a description unlike this one. Do better.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue2.jpg?alt=media&token=42236c82-d174-4542-9a09-146dab7c34fb",  33.810406, -84.447684),
    Picture(3,"blue", "Descriptions are hard to come up with.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue3.jpg?alt=media&token=f101b19b-3392-4999-96c8-87bec71ba198",  47.592572, -122.335207),
    Picture(4,"blue", "How does anyone in this world have time to make up descriptions? Annoying.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue4.jpg?alt=media&token=c0e95d6c-a164-4779-b99f-f280824209e4",  41.789882, -87.718564),
    Picture(5,"blue", "Three word description.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue5.jpg?alt=media&token=e8be01ac-d5ee-4253-ac58-e12a35b94c5a",  32.965647, -96.793393),
    Picture(6,"blue", "Sometimes the best description is the one you don't think a lot about.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue6.jpg?alt=media&token=85fb631c-e9f5-42ee-b7b9-38de4f1ffa1d",  40.615809, -73.984574),
    
    Picture(7, "green", "Do me a favor and don't read this description, it's bad.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fgreen%2Fgreen1.jpg?alt=media&token=88ffcd8f-0840-4c22-88c9-2a2c6c88d7dd",  32.886111, -96.735715),
    Picture(8,"green", "I wanted to write a description that wouldn't make eyes roll but here we are.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fgreen%2Fgreen2.jpg?alt=media&token=d6de137d-2ed4-4229-b3a4-5eae082a32ac",  41.966681, -87.643727),
    Picture(9,"green", "Legend says that in a week I will still be writing descriptions for dummyPictures list.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fgreen%2Fgreen3.jpg?alt=media&token=89c9711c-a07d-4b00-b0f0-f7eb706dace2",  38.536948, -121.440176),
    Picture(10,"green", "I am only halfway there, this seems like an eternity.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fgreen%2Fgreen4.jpg?alt=media&token=8687605e-0320-40e0-ac03-dd0d4392dbd1",  47.592572, -122.335207),
    Picture(11,"green", "Do yourself a favor and autogenerate some random sentences next time.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fgreen%2Fgreen5.jpg?alt=media&token=782f58a9-711b-4bd3-acca-58e36eda367b", 40.761593, -73.252610),
   
    Picture(12,"orange", "Random sentences generator gave me rather dumb examples.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Forange%2Forange1.jpg?alt=media&token=2c2c9084-86ad-4cfe-b147-214325f5a055",  33.719074, -84.389319),
    Picture(13,"orange", "Another short one.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Forange%2Forange2.webp?alt=media&token=ca75ca3e-f884-4452-bcb0-657ebe687c69",  32.788033, -96.856565),
    Picture(14,"orange", "Do other people have issues like this? Suppose so, perhaps I am too much of a Negative Nelly.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Forange%2Forange3.jpg?alt=media&token=6e89cead-0816-433c-a140-d63ea5d3296a",  38.594931, -121.486181),
    Picture(15,"orange", "This is the 26th description to a dummy picture I have written.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Forange%2Forange4.jpg?alt=media&token=4e772f6e-1d03-4a8c-8f47-cdac20e15835",  40.906020, -72.991684),
    Picture(16,"orange", "I truly hope these pictures and descriptions will render correctly.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Forange%2Forange5.jpg?alt=media&token=01afc2af-87cb-4b65-ab3a-4239a6020c87", 38.510626, -121.525320),
    
    Picture(17,"pink", "Place your bets on how long it will take me to finish this app. I bet I am going to lose my senses before it happens.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpink%2Fpink1.jpeg?alt=media&token=b989b066-5fb3-454d-bf30-2efda7eb9dd2",  41.659204, -87.602745),
    Picture(18,"pink", "Not the last one.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpink%2Fpink2.jpg?alt=media&token=bd2ea747-38d9-47cc-aa7e-0d327bc6c691",  40.945449, -73.785447),
    Picture(19,"pink", "Descriptions are hard to come up with.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpink%2Fpink4.jpg?alt=media&token=bc799d7c-6c54-433c-8561-1fe156d5a16f",  47.682331, -122.294008),
    Picture(20,"pink", "How does anyone in this world have time to make up descriptions? Annoying.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpink%2Fpink3.webp?alt=media&token=16427050-6b1c-4f16-9997-aebb027dd36f", 41.764791, -87.579518),
    Picture(21,"pink", "Three word description.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpink%2Fpink5.jpg?alt=media&token=b1a1f039-f1be-4d22-afca-328bdd57f767",  33.761898, -84.340567),
    
    Picture(22,"purple", "Sometimes the best description is the one you don't think a lot about.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpurple%2Fpurple1.jpg?alt=media&token=53494659-f9f7-4166-a09c-a1f0e78e882a",  40.533404, -74.153489),
    Picture(23, "purple", "Do me a favor and don't read this description, it's bad.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpurple%2Fpurple2.jpg?alt=media&token=6a9d9ea5-8538-4ebb-a92b-a94f1e261055",  41.855119, -87.732813),
    Picture(24,"purple", "I wanted to write a description that wouldn't make eyes roll but here we are.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpurple%2Fpurple3.jpg?alt=media&token=a75bedde-e9d7-4080-a6d1-8058a75be0a1",  32.800731, -96.505002),
    Picture(25,"purple", "Legend says that in a week I will still be writing descriptions for dummyPictures list.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fpurple%2Fpurple4.jpeg?alt=media&token=46661c21-2e06-48b3-9669-c2dfc4a9ef33",  47.618498, -122.296068),
    
    Picture(26,"red", "I am only halfway there, this seems like an eternity.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred1.jpg?alt=media&token=776ada3b-f2a5-4f60-b196-2eecbd260b64",  33.741916, -84.486136),
    Picture(27,"red", "Do yourself a favor and autogenerate some random sentences next time.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred2.jpg?alt=media&token=343b6997-e1f5-44c3-9a15-13a9ae4ed6de", 38.479456, -121.435369),
    Picture(28,"red", "Random sentences generator gave me rather dumb examples.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred3.jpg?alt=media&token=5c209084-f094-4a46-aba0-4012e0f1bb9b",  32.707181, -96.709623),
    Picture(29,"red", "Another short one.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred4.jpg?alt=media&token=8dbaa8ce-b5bf-4a08-9483-a4614ec1b5c5",  38.573998, -121.424383),
    Picture(30,"red", "Do other people have issues like this? Suppose so, perhaps I am too much of a Negative Nelly.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred5.jpg?alt=media&token=9d1fe14c-46c0-41e2-b219-b336eb36fd6f",  38.655013, -121.436743),
    Picture(31,"red", "This is the 26th description to a dummy picture I have written.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred6.jpg?alt=media&token=b2899ff5-b8b3-4f50-a68a-01aa2be5a02a",  47.686953, -122.357866),
    Picture(32,"red", "I truly hope these pictures and descriptions will render correctly.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred7.webp?alt=media&token=3c1331df-6275-4f9f-9e44-549e3b3f9baa", 33.771031, -84.421591),
    Picture(33,"red", "Place your bets on how long it will take me to finish this app. I bet I am going to lose my senses before it happens.", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred8.jpg?alt=media&token=af78ef93-1ac0-4978-80b3-51b4af69fe9e",  32.694469, -96.952695),
]

def pic_to_dict(pic):
    tags = ["pretty", "bright", "flower", "spring", "happy", "nice", "color", "wonder", "beautiful", "nature", "wild"]
    ranTags = random.sample(tags, random.randint(0, len(tags)-1))
    tagList = ""

    for tag in ranTags:
        tagList += f"{tag},"
    tagList = tagList[:-1]

    dict = {"id": f"{pic.id}", "handle": f"{pic.handle}", "description": f"{pic.description}", "resource": f"{pic.resource}", "lat": f"{pic.lat}", "lng": f"{pic.lng}", "hashtags": f"{tagList}"}
    return dict

dict = {}

for pic in dummyPictures:
    dict[f"picture{pic.id}"] = pic_to_dict(pic)

print(dict)

with open("pictures.json", "w") as f:
    json.dump(dict, f, indent=2)