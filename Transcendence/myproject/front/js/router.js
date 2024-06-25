const csrfCookieName = 'csrftoken';

function setCSRFCookie(csrfToken) {
  document.cookie = `${csrfCookieName}=${csrfToken}; path=/`;
}

async function getCSRFToken() {
      try {
          const response = await fetch('/api/get-csrf-token/', {
              method: 'GET',
              credentials: 'same-origin'
          });
          if (!response.ok) {
              window.location.href = '/#login';
          }
          const data = await response.json();
          let csrfToken = data.csrfToken;
          if (csrfToken) {
              document.cookie = `${csrfCookieName}=${csrfToken}; path=/`;
              return csrfToken;
          }
      } catch (error) {
            logout();
      }
  
}

document.addEventListener('DOMContentLoaded', function() {
    loadUser();
    initializeWebSocket();
    const userInfo = document.querySelector('.user-info');
    const dropdownMenu = document.getElementById('dropdown-menu');

    userInfo.addEventListener('mouseenter', function() {
        dropdownMenu.style.display = 'flex';
    });

    userInfo.addEventListener('mouseleave', function() {
        setTimeout(function() {
            if (!dropdownMenu.matches(':hover')) {
                dropdownMenu.style.display = 'none';
            }
        }, 200);
    });

    dropdownMenu.addEventListener('mouseleave', function() {
        dropdownMenu.style.display = 'none';
    });

    dropdownMenu.addEventListener('mouseenter', function() {
        dropdownMenu.style.display = 'flex';
    });
});

function SigninURL() {
    const currentURL = new URL(window.location.href);
    const referralURL = encodeURIComponent(currentURL.origin);
    let backendSigninURL = `api/oauth/login/?referral_url=${referralURL}`;
    
  return backendSigninURL;
  }
  

async function verifyAndRefreshToken() {
    const accessToken = localStorage.getItem('token');
    const refreshToken = localStorage.getItem('refresh_token');
    if (!accessToken || !refreshToken) {
        logout();
        window.location.href = '/#login';
        return false;
    }
    const newAccessToken = await refreshAccessToken(refreshToken);

    try {
        const decodedToken = jwt_decode(accessToken);
        const isExpired = decodedToken.exp * 1000 < Date.now();

        if (!isExpired) {
            return true;
        }
        const newAccessToken = await refreshAccessToken(refreshToken);
        if (newAccessToken) {
            localStorage.setItem('token', newAccessToken);
            return true;
        }
    } catch (error) {
        logout();
    }
    return false;
}

async function refreshAccessToken(refreshToken) {
    try {
        const csrf = await getCSRFToken();
        const response = await fetch('/api/token/refresh/', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'X-CSRFToken': csrf
            },
            body: JSON.stringify({ refresh: refreshToken })
        });
        const data = await response.json();
        if (response.ok) {
            localStorage.setItem('token', data.access);
            return data.access;
        }
        throw new Error('Failed to refresh token');
    } catch (error) {
        logout();
    }
}

function getUrlParams() {
    var params = {};
    path = window.location.hash;
    path.split("&").forEach(function(item) {
        var param = item.split("=");
        params[param[0]] = param[1];
    });
    return params;
}

function storeTokensFromUrl() {
    var params = getUrlParams();
    var accessToken = params['#return?access_token'];
    var refreshToken = params['refresh_token'];

    if (accessToken && refreshToken) {
        localStorage.setItem('token', accessToken);
        localStorage.setItem('refresh_token', refreshToken);
    }
    window.location.href = '/#';
}


const checkAuthentication = async () => {
    const currentPath = window.location.hash;
    const nonAuthPaths = ['#login'];
    currentPathSplitted = currentPath.split('?')[0];
    if (currentPathSplitted === '#return') {
        storeTokensFromUrl();
    }

    if (!nonAuthPaths.includes(currentPath)) {
        const isAuthenticated = await verifyAndRefreshToken();
        if (!isAuthenticated && !nonAuthPaths.includes(currentPath)) {
            window.location.href = '/#login';
        } else if (isAuthenticated && nonAuthPaths.includes(currentPath)) {
            window.location.href = '/#';
        }
    }

};

const route = (event) => {
    event = event || window.event;
    event.preventDefault();
    window.history.pushState({}, '', event.target.href);
    handleLocation();
};

const routes = {
    404: '/templates/404.html',
    '#': '/templates/home.html',
    '*': '/templates/home.html',
    '/': '/templates/home.html',
    '': '/templates/home.html',
    '#home': '/templates/home.html',
    '#test': '/templates/test.html',
    '#pong_training/': '/templates/pong.html',
    '#login': '/templates/login.html',
    '#tournament' : '/templates/tournament/tournament.html',
    '#details/' : '/templates/tournament/details.html',
    '#teams_play/' : '/templates/tournament/teams_play.html',
    '#pong/' : '/templates/tournament/pong.html',
    '#user_info/' : '/templates/user/user_info.html',
    '#profile/' : '/templates/user/profil.html',
    '#return' : '/templates/return.html',
    '#chat/' : '/templates/chat.html',
    
}

let previousPath = '';

function showLoaderDefault() {
    const loaderHandler = document.querySelector('.loader');
    const loaderContainer = document.createElement('div');
    loaderContainer.classList.add('loader-container-default');
    loaderContainer.innerHTML = `
        <svg class="loader-svg" xmlns="http://www.w3.org/2000/svg" xml:space="preserve" viewBox="0 -200 960 960">
            <path id="path1" d="M32 412.6h330.1V578h164.7V279.1H197.3L526.8-51.1H362.1L32 279.1zM597.9 114.2 762.7-51.1H597.9zM762.7 114.2 597.9 279.1v164.8h164.8V279.1L928 114.2V-51.1H762.7z"/>
            <path id="path2" d="M928 279.1 762.7 443.9H928z"/>
        </svg>
    `;
    loaderHandler.appendChild(loaderContainer);
    loaderContainer.style.display = 'block';
}

function hideLoaderDefault() {
    const loaderContainer = document.querySelector('.loader');
    if (loaderContainer) {
        loaderContainer.style.display = 'none';
    }
}

const handleLocation = async () => {
    
    checkAuthentication();
    
    if (!window.location.hash || window.performance.getEntriesByType("navigation")[0].type === "reload") {
        showLoaderDefault();
    }

    let path = window.location.hash || '#'; 
    const questionMarkIndex = path.indexOf('?');
    if (questionMarkIndex !== -1) {
      path = path.slice(0, questionMarkIndex);
    }

    let id = null;
    if (path.startsWith('#details/')) {
        id = path.split('/')[1];  
        path = '#details/';  
    }
    else if (path.startsWith('#teams_play/')) {
        id = path.split('/')[1];  
        path = '#teams_play/';  
    }
    else if (path.startsWith('#pong/')) {
        id = path.split('/')[1];  
        path = '#pong/';  
    }
    else if (path.startsWith('#user_info/')) {
        id = path.split('/')[1];  
        path = '#user_info/';  
    } else if (path === '#profile/') {
        fetchUser()
    } else if (path.startsWith('#chat/')) {
        id = path.split('/')[1];  
        path = '#chat/';  
    }

    if (path !== previousPath) {
        const noCore = ['#login'];
        if (noCore.includes(path)) {
            const core = document.getElementById("core");
            core.classList.add('hidden');
            const route = routes[path] || routes[404];
            const html = await fetch(route).then((data) => data.text());
            const container = document.getElementById("login-container");
            container.classList.remove('hidden');
            container .innerHTML = html;
            if (path === '#login') {
                loginAnimation();
            }
        } else {
            if (previousPath === '#pong_training/') {
                PongIA.destroy();
                PongT.destroy();
            } else if (previousPath === '#pong/') {
                Pong.destroy();
            }
            const container = document.getElementById("login-container");
            container.classList.add('hidden');
            const route = routes[path] || routes[404];
            const html = await fetch(route).then((data) => data.text());
            const core = document.getElementById("core");
            core.classList.remove('hidden');
            core.classList.add('fade-in');
            document.getElementById("app").innerHTML = html;
            if (id && path === '#details/') {
                loadTournamentDetails(id);
            }
            else if (id && path === '#teams_play/') {
                loadTournamentTeams(id);
            }
            else if (id && path === '#pong/') {
                loadTournamentPlay(id);
            }
            else if (id && path === '#user_info/') {
                loadUserInfo(id);
            } else if (id && path === '#chat/') {
                fetchMessages(id);
            }
        }
        
        previousPath = path;
    }
    setTimeout(() => {
        hideLoaderDefault();
    }, 1000);
};

window.onpopstate = handleLocation;
window.route = route;
handleLocation();