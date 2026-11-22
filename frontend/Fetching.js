// Fetching with JS and later with TypeScript


async function visualization() {

    try {
        const res = await fetch ("/api/visualization");

        const data = await res.json();
        
        console.log("Received Hex String: ", data.hex);

        document.getElementById("hex-output").textContent = data.hex;

    } catch (error) {
        console.error("Error: ", error);
    }
};
