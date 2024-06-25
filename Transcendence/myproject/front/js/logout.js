
async function logout() {
    const refresh = localStorage.getItem('refresh_token');
    const id = localStorage.getItem('userId');
    const csrf = await getCSRFToken();
    var formData = new FormData();
    formData.append("refresh_token", refresh);
    formData.append("id", id);
    try {
        const response = await fetch("/api/logout/", {
            method: "POST",
            body: formData,
            headers: {
                'X-CSRFToken': csrf,
            },
        });
        if (response.status === 204) {
            localStorage.removeItem('refresh_token');
            localStorage.removeItem('token');
            localStorage.removeItem('username');
            localStorage.removeItem('recipientImg');
            localStorage.removeItem('recipientName');
            localStorage.removeItem('recipientId');
            localStorage.removeItem('userName');
            localStorage.removeItem('userImg');
            localStorage.removeItem('userId');
            window.location.href = '/#login';
            
        }
    } catch (error) {}
}