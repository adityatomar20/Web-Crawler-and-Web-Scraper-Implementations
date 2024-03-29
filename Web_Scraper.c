rom requests import get
url = 'http://www.imdb.com/search/title?release_date=2018&sort=num_votes,desc&page=1'
response = get(url)
print(response.text)

from bs4 import BeautifulSoup
html_soup = BeautifulSoup(response.text, 'html.parser')
type(html_soup)

movie_containers = html_soup.find_all('div', class_ = 'lister-item mode-advanced')

names = []
years = []
imdb_ratings = []
metascores = []
# Extract data from individual movie container
for container in movie_containers:
	# If the movie has Metascore, then extract:
	if container.find('div', class_ = 'ratings-metascore') is not None:
    	# The name
    	name = container.h3.a.text
    	names.append(name)
    	# The year
    	year = container.h3.find('span', class_ = 'lister-item-year').text
    	years.append(year)
    	# The IMDB rating
    	imdb = float(container.strong.text)
    	imdb_ratings.append(imdb)
    	# The Metascore
    	m_score = container.find('span', class_ = 'metascore').text
    	metascores.append(int(m_score))
	 
import pandas as pd
test_df = pd.DataFrame({'movie': names,
                   	'year': years,
                   	'imdb': imdb_ratings,
                   	'metascore': metascores
})
print(test_df.info())
