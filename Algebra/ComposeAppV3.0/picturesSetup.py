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
    Picture(1,"blue", "I had a lovely day today, yall. Hopefully tomorrow is as good.", "gs://composeapp-47d09.appspot.com/pictures/blue/blue1.jpg",  40.758105, -73.702477),
    Picture(2,"blue", "Once upon a time there was a description unlike this one. Do better.", "gs://composeapp-47d09.appspot.com/pictures/blue/blue2.jpg",  33.810406, -84.447684),
    Picture(3,"blue", "Descriptions are hard to come up with.", "gs://composeapp-47d09.appspot.com/pictures/blue/blue3.jpg",  47.592572, -122.335207),
    Picture(4,"blue", "How does anyone in this world have time to make up descriptions? Annoying.", "gs://composeapp-47d09.appspot.com/pictures/blue/blue4.jpg",  41.789882, -87.718564),
    Picture(5,"blue", "Three word description.", "gs://composeapp-47d09.appspot.com/pictures/blue/blue5.jpg",  32.965647, -96.793393),
    Picture(6,"blue", "Sometimes the best description is the one you don't think a lot about.", "gs://composeapp-47d09.appspot.com/pictures/blue/blue6.jpg",  40.615809, -73.984574),
    
    Picture(7, "green", "Do me a favor and don't read this description, it's bad.", "gs://composeapp-47d09.appspot.com/pictures/green/green1.jpg",  32.886111, -96.735715),
    Picture(8,"green", "I wanted to write a description that wouldn't make eyes roll but here we are.", "gs://composeapp-47d09.appspot.com/pictures/green/green2.jpg",  41.966681, -87.643727),
    Picture(9,"green", "Legend says that in a week I will still be writing descriptions for dummyPictures list.", "gs://composeapp-47d09.appspot.com/pictures/green/green3.jpg",  38.536948, -121.440176),
    Picture(10,"green", "I am only halfway there, this seems like an eternity.", "gs://composeapp-47d09.appspot.com/pictures/green/green4.jpg",  47.592572, -122.335207),
    Picture(11,"green", "Do yourself a favor and autogenerate some random sentences next time.", "gs://composeapp-47d09.appspot.com/pictures/green/green5.jpg", 40.761593, -73.252610),
   
    Picture(12,"orange", "Random sentences generator gave me rather dumb examples.", "gs://composeapp-47d09.appspot.com/pictures/orange/orange1.jpg",  33.719074, -84.389319),
    Picture(13,"orange", "Another short one.", "gs://composeapp-47d09.appspot.com/pictures/orange/orange2.webp",  32.788033, -96.856565),
    Picture(14,"orange", "Do other people have issues like this? Suppose so, perhaps I am too much of a Negative Nelly.", "gs://composeapp-47d09.appspot.com/pictures/orange/orange3.jpg",  38.594931, -121.486181),
    Picture(15,"orange", "This is the 26th description to a dummy picture I have written.", "gs://composeapp-47d09.appspot.com/pictures/orange/orange4.jpg",  40.906020, -72.991684),
    Picture(16,"orange", "I truly hope these pictures and descriptions will render correctly.", "gs://composeapp-47d09.appspot.com/pictures/orange/orange5.jpg", 38.510626, -121.525320),
    
    Picture(17,"pink", "Place your bets on how long it will take me to finish this app. I bet I am going to lose my senses before it happens.", "gs://composeapp-47d09.appspot.com/pictures/pink/pink1.jpeg",  41.659204, -87.602745),
    Picture(18,"pink", "Not the last one.", "gs://composeapp-47d09.appspot.com/pictures/pink/pink2.jpg",  40.945449, -73.785447),
    Picture(19,"pink", "Descriptions are hard to come up with.", "gs://composeapp-47d09.appspot.com/pictures/pink/pink3.webp",  47.682331, -122.294008),
    Picture(20,"pink", "How does anyone in this world have time to make up descriptions? Annoying.", "gs://composeapp-47d09.appspot.com/pictures/pink/pink4.jpg", 41.764791, -87.579518),
    Picture(21,"pink", "Three word description.", "gs://composeapp-47d09.appspot.com/pictures/pink/pink5.jpg",  33.761898, -84.340567),
    
    Picture(22,"purple", "Sometimes the best description is the one you don't think a lot about.", "gs://composeapp-47d09.appspot.com/pictures/purple/purple1.jpg",  40.533404, -74.153489),
    Picture(23, "purple", "Do me a favor and don't read this description, it's bad.", "gs://composeapp-47d09.appspot.com/pictures/purple/purple2.jpg",  41.855119, -87.732813),
    Picture(24,"purple", "I wanted to write a description that wouldn't make eyes roll but here we are.", "gs://composeapp-47d09.appspot.com/pictures/purple/purple3.jpg",  32.800731, -96.505002),
    Picture(25,"purple", "Legend says that in a week I will still be writing descriptions for dummyPictures list.", "gs://composeapp-47d09.appspot.com/pictures/purple/purple4.jpeg",  47.618498, -122.296068),
    
    Picture(26,"red", "I am only halfway there, this seems like an eternity.", "gs://composeapp-47d09.appspot.com/pictures/red/red1.jpg",  33.741916, -84.486136),
    Picture(27,"red", "Do yourself a favor and autogenerate some random sentences next time.", "gs://composeapp-47d09.appspot.com/pictures/red/red2.jpg", 38.479456, -121.435369),
    Picture(28,"red", "Random sentences generator gave me rather dumb examples.", "gs://composeapp-47d09.appspot.com/pictures/red/red3.jpg",  32.707181, -96.709623),
    Picture(29,"red", "Another short one.", "gs://composeapp-47d09.appspot.com/pictures/red/red4.jpg",  38.573998, -121.424383),
    Picture(30,"red", "Do other people have issues like this? Suppose so, perhaps I am too much of a Negative Nelly.", "gs://composeapp-47d09.appspot.com/pictures/red/red5.jpg",  38.655013, -121.436743),
    Picture(31,"red", "This is the 26th description to a dummy picture I have written.", "gs://composeapp-47d09.appspot.com/pictures/red/red6.jpg",  47.686953, -122.357866),
    Picture(32,"red", "I truly hope these pictures and descriptions will render correctly.", "gs://composeapp-47d09.appspot.com/pictures/red/red7.webp", 33.771031, -84.421591),
    Picture(33,"red", "Place your bets on how long it will take me to finish this app. I bet I am going to lose my senses before it happens.", "gs://composeapp-47d09.appspot.com/pictures/red/red8.jpg",  32.694469, -96.952695),
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