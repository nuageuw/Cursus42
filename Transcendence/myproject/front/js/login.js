let notificationQueueLogin = [];

function showNotificationLogin(message, colorIndex = 1) {
    notificationQueueLogin.push({ message, colorIndex });
    if (notificationQueueLogin.length === 1) {
        displayNextNotificationLogin();
    }
}

function displayNextNotificationLogin() {
    if (notificationQueueLogin.length === 0) {
        return;
    }

    const notificationsContainer = document.getElementById('login-notifications-containers');
    const { message, colorIndex } = notificationQueueLogin.shift();
    const notificationBox = document.createElement('div');
    notificationBox.className = `notification-box color-${colorIndex} show`;
    notificationBox.textContent = message;
    notificationsContainer.appendChild(notificationBox);

    setTimeout(() => {
        notificationBox.classList.remove('show');
        notificationBox.classList.add('hide');
    }, 3000);

    setTimeout(() => {
        notificationsContainer.removeChild(notificationBox);
        displayNextNotificationLogin();
    }, 3500);
}


async function loginUser() {
    var username = document.getElementById("login-username").value;
    var password = document.getElementById("login-password").value;
    const csrf = await getCSRFToken();
    const button = document.getElementById('login-button');
    button.disabled = true;

    var formData = new FormData();
    formData.append("email", username);
    formData.append("password", password);

    try {
        const response = await fetch("/api/login/", {
            method: "POST",
            body: formData,
            headers: {
                'X-CSRFToken': csrf,
            },
        });
        const data = await response.json();
        if (response.ok) {
            if (data.first_connection) {
                localStorage.setItem('token', data.access_token);
                localStorage.setItem('refresh_token', data.refresh_token);
                localStorage.setItem('username', data.username);
                showLoader();
                showNotificationLogin('✅ Login successful', 2);
                setTimeout(() => {
                    hideLoader();
                    show2FASetup();
                } , 2000);
            } else if (data.fa_required) {
                localStorage.setItem('username', data.username);
                showLoader();
                setTimeout(() => {
                    hideLoader();
                    verify2FA();
                } , 1500);
            } else {
                showLoader();
                showNotificationLogin('✅ Login successful', 2);
                setTimeout(() => {
                    hideLoader();
                    completeLogin(data);
                } , 1500);
            }
        } else {
            showNotificationLogin("❌ " + (data.detail || data.email || data.error || data.password), 3);
        }
    } catch (error) {
        showNotificationLogin('An error occurred: ' + error.message);
    }
    setTimeout(() => {
        button.disabled = false;
    }, 300);
}

async function registerUser() {
    var username = document.getElementById("register-username").value;
    var email = document.getElementById("register-email").value;
    var password = document.getElementById("register-password").value;
    var password2 = document.getElementById("conf-password").value;

    var formData = new FormData();
    formData.append("username", username);
    formData.append("email", email);
    formData.append("password", password);
    formData.append("password2", password2);

    const csrf = await getCSRFToken();

    try {
        const response = await fetch("/api/register/", {
            method: "POST",
            body: formData,
            headers: {
                'X-CSRFToken': csrf,
            },
        });
        const data = await response.json();
        if (response.ok) {
            showNotificationLogin('✅ Registration successful', 2);
            showLogin();
        } else {
            showNotificationLogin("❌ " + (data.password || data.email || data.error), 3);
        }
    } catch (error) {
        showNotificationLogin('An error occurred: ' + error.message);
    }
}

async function verify2FA() {
    const authWrapper = document.querySelector('.auth-wrapper');
    authWrapper.classList.add('expand');
    setTimeout(() => {
        const faVerif = document.getElementById('2fa-verification');
        const registerForm = document.getElementById('register');
        const loginForm = document.getElementById('login');
        const authForms = document.querySelector('.auth-forms');
        registerForm.remove();
        loginForm.remove();
        authForms.style.minHeight = '400px';
        authForms.style.width = '100%';
        faVerif.classList.remove('hidden');
        faVerif.classList.add('visible');
        faVerif.classList.add('fade-in');
        faVerif.style.width = '100%';
    }, 500);
    
}

function completeLogin(data) {
    localStorage.setItem('token', data.access_token);
    localStorage.setItem('refresh_token', data.refresh_token);
    localStorage.setItem('username', data.username);
    const container = document.querySelector('.login-container');
    container.classList.add('fade-out');
    setTimeout(() => {
        loadUser();
        initializeWebSocket();
        window.location.href = '/#';
    }, 500);
}

function showLogin() {
    const authForms = document.querySelector('.auth-forms');
    authForms.style.transform = 'translateX(0)';

    const tabSlider = document.getElementById('tab-slider');
    tabSlider.style.left = '0';

    document.getElementById('login').classList.add('active');
    document.getElementById('register').classList.remove('active');

    document.getElementById('login-tab').classList.add('active');
    document.getElementById('register-tab').classList.remove('active');
}

function showRegister() {
    const authForms = document.querySelector('.auth-forms');
    authForms.style.transform = 'translateX(-50%)';

    const tabSlider = document.getElementById('tab-slider');
    tabSlider.style.left = '50%';

    document.getElementById('login').classList.remove('active');
    document.getElementById('register').classList.add('active');

    document.getElementById('login-tab').classList.remove('active');
    document.getElementById('register-tab').classList.add('active');
}

function loginAnimation() {
    const pageContainer = document.querySelector('.login-handler');
    pageContainer.classList.add('slide-up');
}

function showLoader() {
    const authForm = document.querySelector('.auth-form.active');
    const authTabs = document.querySelector('.auth-tabs');
    authTabs.style.display = 'none';
    authForm.style.display = 'none';
    
    const loaderHandler = document.querySelector('.loader-handler');
    const loaderContainer = document.createElement('div');
    loaderContainer.classList.add('loader-container');
    loaderContainer.innerHTML = `
        <svg class="loader-svg" xmlns="http://www.w3.org/2000/svg" xml:space="preserve" viewBox="0 -200 960 960">
            <path id="path1" d="M32 412.6h330.1V578h164.7V279.1H197.3L526.8-51.1H362.1L32 279.1zM597.9 114.2 762.7-51.1H597.9zM762.7 114.2 597.9 279.1v164.8h164.8V279.1L928 114.2V-51.1H762.7z"/>
            <path id="path2" d="M928 279.1 762.7 443.9H928z"/>
        </svg>
    `;
    loaderHandler.appendChild(loaderContainer);
}

function hideLoader() {
    const loaderContainer = document.querySelector('.loader-container');
    if (loaderContainer) {
        loaderContainer.classList.add('fade-out');
        setTimeout(() => {
            loaderContainer.remove();
        }, 500);
    }
}

function show2FASetup() {
    const authWrapper = document.querySelector('.auth-wrapper');
    authWrapper.classList.add('expand');
    const username = localStorage.getItem('username');
    const usernamePlaceholder = document.getElementById('username-placeholder');
    if (username) {
        usernamePlaceholder.textContent = username;
    } else {
        usernamePlaceholder.textContent = 'Utilisateur';
    }

    setTimeout(() => {
        const faAsk = document.getElementById('2fa-ask');
        const registerForm = document.getElementById('register');
        const loginForm = document.getElementById('login');
        const authForms = document.querySelector('.auth-forms');
        registerForm.remove();
        loginForm.remove();
        authForms.style.minHeight = '400px';
        authForms.style.width = '100%';
        faAsk.classList.remove('hidden');
        faAsk.classList.add('visible');
        faAsk.classList.add('fade-in');
        faAsk.style.width = '100%';
    }, 500);
}

async function setup2FA() {
    const faAsk = document.getElementById('2fa-ask');
    faAsk.classList.add('fade-out');
    faAsk.classList.remove('visible');
    faAsk.classList.add('hidden');
    const authWrapper = document.querySelector('.auth-wrapper');
    authWrapper.classList.add('expandPlus');
    setTimeout(() => {
        const faSteps = document.getElementById('2fa-steps');
        faSteps.classList.remove('hidden');
        faSteps.classList.add('visible');
        faSteps.classList.add('fade-in');
    }, 500);
    var form = document.getElementById('activate2FAForm');
    var formData = new FormData(form);
    const csrf = await getCSRFToken();
    const accessToken = localStorage.getItem('token');

    try {
        const response = await fetch('/api/2fa/enable/', {
            method: 'POST',
            body: formData,
            headers: {
                'Authorization': `Bearer ${accessToken}`,
                'X-CSRFToken': csrf,
            },
        });
        if (response.ok) {
            const data = await response.json();
            displayQRCode(data);
        }
    } catch (error) {}
}

function displayQRCode(response) {
    var qrCodeBase64 = response.qr_code_base64;
    var qrCodeContainer = document.getElementById('qrCodeContainer');
    qrCodeContainer.innerHTML = '<img src="data:image/png;base64,' + qrCodeBase64 + '" alt="QR Code">';
    qrCodeContainer.style.display = 'block';
    qrCodeContainer.style.margin = '50px';
}

function skip2FA() {
    showProfilePhotoSetup();
}

async function test2FA(otpCode) {
    var formData = new FormData();
    formData.append('otp_code', otpCode);
    const accessToken = localStorage.getItem('token');
    const csrf = await getCSRFToken();

    try {
        const response = await fetch('/api/2fa/verify/', {
            method: 'POST',
            body: formData,
            headers: {
                'Authorization': `Bearer ${accessToken}`,
                'X-CSRFToken': csrf,
            },
        });

        if (response.ok) {
            const faSteps = document.getElementById('2fa-steps');
            faSteps.classList.remove('fade-in');
            faSteps.classList.add('fade-out');
            setTimeout(() => {
                faSteps.classList.remove('visible');
                faSteps.classList.add('hidden');
                const checkMark = document.getElementById('verificationResult');
                checkMark.innerHTML = '<svg xmlns="http://www.w3.org/2000/svg" x="0px" y="0px" width="100" height="100" viewBox="0 0 48 48"><path fill="#c8e6c9" d="M44,24c0,11.045-8.955,20-20,20S4,35.045,4,24S12.955,4,24,4S44,12.955,44,24z"></path><path fill="#4caf50" d="M34.586,14.586l-13.57,13.586l-5.602-5.586l-2.828,2.828l8.434,8.414l16.395-16.414L34.586,14.586z"></path></svg>';
                checkMark.classList.remove('hidden');
                checkMark.classList.add('visible');
                checkMark.classList.add('fade-in');
                setTimeout(() => {
                    checkMark.classList.remove('fade-in');
                    checkMark.classList.add('fade-out');
                    checkMark.remove();
                    showProfilePhotoSetup();
                }, 900);
            } , 800);
        } else {
            const data = await response.json();
            showNotificationLogin('❌ Le code OTP est invalide.', 3);
        }
    } catch (error) {
        showNotificationLogin('❌ An error occured while checking OTP code.', 3);
    }
}

async function test_2fa(event) {
    var otpCode = document.getElementById('otpCodeInput').value;
    await test2FA(otpCode); 
}

async function send2FA() {
    var otpCode = document.getElementById('otpVerifInput').value;
    var formData = new FormData();
    formData.append('otp_code', otpCode);
    formData.append('username', localStorage.getItem('username'));
    const accessToken = localStorage.getItem('token');
    const csrf = await getCSRFToken();

    try {
        const response = await fetch('/api/2fa/verify/', {
            method: 'POST',
            body: formData,
            headers: {
                'X-CSRFToken': csrf,
            },
        });

        if (response.ok) {
            const data = await response.json();
            showNotificationLogin('✅ Code valid', 2);
            setTimeout(() => {
                completeLogin(data);
            }, 2000);
        } else {
            const data = await response.json();
            showNotificationLogin('❌ OTP Code invalid', 3);
        }
    } catch (error) {
        showNotificationLogin('❌ An error occured while checking code', 3);
    }
}

let selectedImage = null;

function showProfilePhotoSetup() {
    const faSteps = document.getElementById('2fa-steps');
    const faAsk = document.getElementById('2fa-ask');
    const authWrapper = document.querySelector('.auth-wrapper');
    if(faSteps) {
        faSteps.remove();
        authWrapper.classList.add('expandPlusPlus');
    } 
    if (faAsk) {
        faAsk.classList.add('fade-out');
        faAsk.classList.remove('visible');
        faAsk.classList.add('hidden');
        authWrapper.classList.add('expandMinusPlus');
    }
    setTimeout(() => {
        const photoSetup = document.getElementById('photo-setup');
        photoSetup.classList.remove('hidden');
        photoSetup.classList.add('fade-in');
        photoSetup.innerHTML = `
            <div class="profile-selection">
            <h2>Choose a profile picture</h2>
                <div id="profilePictures" style="margin: 30px;">
                    <img src="/media/profile1.png" alt="Profile 1" onclick="selectImage(this)">
                    <img src="/media/profile2.png" alt="Profile 2" onclick="selectImage(this)">
                    <img src="/media/profile3.png" alt="Profile 3" onclick="selectImage(this)">
                    <img src="/media/profile4.png" alt="Profile 4" onclick="selectImage(this)">
                    <img src="/media/profile5.png" alt="Profile 5" onclick="selectImage(this)">
                </div>
                <button type="button" id="uploadCustomButton" onclick="uploadCustomPhoto()">Upload a custom photo</button>
    <input type="file" id="customPhotoInput" style="display: none;" onchange="previewCustomPhoto()">
    <button type="submit" id="validateButton" style="display: none;" onclick="validateSelection()">Validate</button>
            </div>
        `;
    } , 800);
}

function selectImage(image) {
    const images = document.querySelectorAll('.profile-selection img');
    images.forEach(img => img.classList.remove('selected'));

    image.classList.add('selected');
    selectedImage = image;

    document.getElementById('validateButton').style.display = 'block';
}

async function validateSelection() {
    if (selectedImage && selectedImage.src.startsWith('data:image')) {
        await uploadCustomImage();
    } else {
        finalizeSelection();
    }
}

async function validateSelection() {
    const profilePictures = document.getElementById('profilePictures');
    const customImageInput = document.getElementById('customPhotoInput');
    const selectedImageSrc = selectedImage ? selectedImage.src : null;
    const file = customImageInput.files[0];
    
    const children = profilePictures.children;
    for (let i = 0; i < children.length; i++) {
        if (children[i] !== selectedImage) {
            children[i].classList.add('hidden');
        }
    }
    if (selectedImage) {
        selectedImage.classList.remove('hidden');
        selectedImage.classList.add('selected');
    }
    
    document.getElementById('validateButton').style.display = 'none';
    
    let formData = new FormData();
    if (file) {
        formData.append('file', file);
    } else if (selectedImageSrc) {
        formData.append('image_link', selectedImageSrc);
    } else {
        showNotificationLogin('❌ No image selected', 3);
        return;
    }
    
    try {
        const csrf = await getCSRFToken();
        const token = localStorage.getItem('token');
        
        const response = await fetch('/api/update_pictures/', {
            method: 'POST',
            body: formData,
            headers: {
                'Authorization': `Bearer ${token}`,
                'X-CSRFToken': csrf,
            },
        });
        
        if (response.ok) {
            showNotificationLogin('✅ Profile image updated', 2);
            setTimeout(() => {
                window.location.href = '/';
            }, 2000);
        } else {
            showNotificationLogin('❌ An error occurred', 3);
        }
    } catch (error) {
        showNotificationLogin('❌ An error occurred: ' + error.message, 3);
    }
}


function uploadCustomPhoto() {
    document.getElementById('customPhotoInput').click();
}

function previewCustomPhoto() {
    const input = document.getElementById('customPhotoInput');
    if (input.files && input.files[0]) {
        const reader = new FileReader();
        reader.onload = function(e) {
            const img = document.createElement('img');
            img.src = e.target.result;
            img.alt = 'Custom Photo';
            img.onclick = () => selectImage(img);
            
            const profilePictures = document.getElementById('profilePictures');
            profilePictures.appendChild(img);

            img.click();
        }
        reader.readAsDataURL(input.files[0]);
    }
}