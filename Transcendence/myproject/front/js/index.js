

async function toggleSearch() {
    let searchForm = document.querySelector('.search-form');
    searchForm.classList.toggle('active');
    const searchBox = document.getElementById('search-box');
    const searchResults = document.getElementById('search-results');
    searchBox.addEventListener('input', function() {
        const query = this.value;
        const token = localStorage.getItem('token');
        if (!token) {
            return;
        }
        if (query.length > 0) {
                fetch(`/api/search_players/?query=${encodeURIComponent(query)}`, {
                    method: 'GET',
                    headers: {
                        'Authorization': `Bearer ${token}`,
                        'Content-Type': 'application/json'
                    }
                })
                .then(response => response.json())
                .then(data => {
                    searchResults.innerHTML = '';
                    if (data.users_data.length > 0) {
                        data.users_data.forEach(user => {
                            if (user.is_registered) {
                                const link = `<a href="#profile/" class="search-result">${user.name}</a>`;
                                searchResults.insertAdjacentHTML('beforeend', link);
                            }
                            else {
                                const link = `<a href="#user_info/${user.id}" class="search-result">${user.name}</a>`;
                                searchResults.insertAdjacentHTML('beforeend', link);
                            }
                        });
                        searchResults.classList.add('active');
                        searchForm.classList.add('modif');
                    } else {
                        searchResults.classList.remove('active');
                        searchForm.classList.remove('modif');
                    }
                })
        } else {
            searchResults.innerHTML = '';
            searchResults.classList.remove('active');
            searchForm.classList.remove('modif');
        }
    });
    window.onscroll = () => {
		searchForm.classList.remove('active');
		if (searchForm.classList.contains('modif')) {
			searchForm.classList.remove('modif');
            searchResults.innerHTML = '';
            searchResults.classList.remove('active');
		}
	}
}

async function loadUser() {
        const url = `/api/profil/`;
        const token = localStorage.getItem('token');
    
        if (!token) {
            return; 
        }
    
        const response = await fetch(url, {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${token}`,
                'Content-Type': 'application/json'
            }
        });
    
        if (!response.ok) {
            const message = `An error has occured: ${response.status}`;
            throw new Error(message);
        }
    
        const userData = await response.json();
    
        const nameElement = document.getElementById('name');
        if (nameElement) {
            nameElement.textContent = `${userData.user_data.username}`;
        } else {
            console.error("Element not found in the document");
        }
        const imgElement = document.getElementById('profile-pic');
        if (imgElement) {
            imgElement.src = `${userData.user_data.img}`;
        } else {
            console.error("Element not found in the document");
        }
    }
    loadUser();

    window.addEventListener('hashchange', function() {
        searchForm =  document.querySelector('.search-form');
        searchResults = document.getElementById('search-results');
        searchForm.classList.remove('active');
		if (searchForm.classList.contains('modif')) {
			searchForm.classList.remove('modif');
            searchResults.innerHTML = '';
            searchResults.classList.remove('active');
		}
      });