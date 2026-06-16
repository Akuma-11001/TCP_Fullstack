// Fetching with JS and later with TypeScript


fetch("/api/login, {
    method: "POST",
    headers: {
        "Content-Type": "appilcation/json"
    },
    body: JSON.stringfy({
        username: "user1"
    })
});
