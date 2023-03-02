import requests as req

# spaces in adresses need to be replaced with %20

try:
    response = req.get('https://catfact.ninja/fact')

    # raises http error if it occured
    response.raise_for_status()

    data = response.json()

    if(response.status_code == 200):
        # request header is a dictionary
        for key in response.headers:
            print(f"{key} = {response.headers[key]}")

        # print(data['fact'])
            
    else:
        print(f"{response.reason}")

    html = response.text

except req.HTTPError as e:
    print(e)

# to navigate json data, use multiple identifiers: data['sth'][1]['name']

### sorting a list: ascending by default or with a lambda
# rated_shows_sorted = sorted(rated_shows, key=reversed)
# rated_shows_sorted = sorted(rated_shows, key=lambda x: x[1])

### UNSTRUCTURED DATA PROCESSING ###
from bs4 import BeautifulSoup as bs     # raw html parser

response = req.get('https://realpython.github.io/fake-jobs/')
soup = bs(response.content, "html.parser")

# filtering through the soup: 
# soup_element.find('elem_name', {"attr:" "value"})

using_id = soup.find(id="ResultsContainer")
card_list = soup.find_all(class_="card")

# if you know the structure of the document:
title = using_id.h2.text

html = soup.prettify()
# print(html[:300])

# saving an image:

try:
    url = 'http://books.toscrape.com/'
    response = req.get(url)
    soup = bs(response.content, "html.parser")

    img = soup.find('img')
    imgUrl = url + img['src']
    resp = req.get(imgUrl)

    with open("image.jpg", "wb") as f:
        f.write(resp.content,)

except req.HTTPError as e:
    print(e)