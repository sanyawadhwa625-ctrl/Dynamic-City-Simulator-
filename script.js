const state = {
    traffic: 32,
    roadsOpen: 6,
    congestion: 32,
    accident: false,
    emergency: false
};

const $ = id => document.getElementById(id);
const logBox = $("log");

function log(message) {
    const line = document.createElement("div");
    line.textContent = "> " + message;
    logBox.prepend(line);
}

function updateStats() {
    $("trafficValue").textContent =
        state.traffic < 50 ? "LOW" : state.traffic < 75 ? "MEDIUM" : "HIGH";
    $("roadValue").textContent = state.roadsOpen;
    $("congestionValue").textContent = state.congestion + "%";
    $("emergencyValue").textContent = state.emergency ? "ACTIVE" : "NONE";
}

document.querySelectorAll(".building").forEach(building => {
    building.addEventListener("click", () => {
        $("objectInfo").innerHTML =
            "<b>" + building.dataset.name + "</b><br>" +
            "Type: " + building.dataset.type + "<br>" +
            "Stored using: Hash Map";
        log("Selected " + building.dataset.name);
    });
});


$("routeBtn").addEventListener("click", async () => {
    const oldLine = $("routeLine");
    const routePath = $("shortestRoutePath");

    if (oldLine) {
        oldLine.style.display = "none";
    }

    if (!routePath) {
        $("routeStatus").textContent = "Route overlay missing";
        log("Could not find shortestRoutePath in index.html.");
        return;
    }

    try {
        const response = await fetch(
            "http://127.0.0.1:5000/city?command=route"
        );

        const data = await response.json();

        if (!response.ok || data.status !== "success") {
            $("routeStatus").textContent = "Backend error";
            log("Backend error: " + (data.message || "Route request failed."));
            return;
        }

        // Coordinates use the SVG viewBox: 1000 x 800.
        // The horizontal segment follows the main road.
        // The upper segment turns toward the hospital-side road.
        
        const normalRoute = [
            [5, 460],
            [180, 460],
            [350, 460],
            [520, 460],
            [680, 460],
            [740, 460],
            [765, 390],
            [785, 310],
            [805, 230],
            [825, 150],
            [840, 100]
        ].map(point => point.join(",")).join(" ");


        // Temporary visual alternative for the accident scenario.
        // This should be replaced with the actual path returned by C.
        const alternateRoute = [
            [35, 495],
            [180, 495],
            [320, 495],
            [460, 495],
            [600, 495],
            [680, 495],
            [700, 535],
            [680, 585],
            [640, 625],
            [580, 650]
        ].map(point => point.join(",")).join(" ");

        routePath.setAttribute(
            "points",
            state.accident ? alternateRoute : normalRoute
        );

        routePath.style.display = "block";

        $("routeStatus").textContent = state.accident
            ? "Alternate route requested"
            : "Shortest route requested";

        document.body.classList.add("route-active");

        log(
            state.accident
                ? "C Backend: Accident scenario processed."
                : "C Backend: Route request completed."
        );

        console.log("C Backend Output:", data.output);

    } catch (error) {
        $("routeStatus").textContent = "Backend connection failed";
        log("Could not connect to C backend.");
        console.error(error);
    }
});



$("trafficBtn").addEventListener("click", async () => {

    state.traffic = Math.min(100, state.traffic + 18);
    state.congestion = Math.min(100, state.congestion + 15);

    $("car1").style.left =
        (18 + state.traffic / 4) + "%";

    $("car2").style.left =
        (50 + state.traffic / 6) + "%";

    updateStats();

    try {

        const response = await fetch(
            "http://127.0.0.1:5000/city?command=traffic"
        );

        const data = await response.json();

        if (data.status === "success") {

            log(
                "C Backend: Traffic vehicles processed using Queue."
            );

            console.log(
                "C Queue Output:",
                data.output
            );

        } else {

            log(
                "Backend error: " + data.message
            );
        }

    } catch (error) {

        log(
            "Could not connect to C Queue backend."
        );

        console.error(error);
    }
});
$("emergencyBtn").addEventListener("click", async () => {

    state.emergency = true;

    const ambulance = $("ambulance");

    ambulance.style.display = "block";
    ambulance.style.left = "30%";
    ambulance.style.top = "325px";

    updateStats();

    try {

        const response = await fetch(
            "http://127.0.0.1:5000/city?command=emergency"
        );

        const data = await response.json();

        if (data.status === "success") {

            log(
                "C Backend: Ambulance inserted into Priority Queue with highest priority."
            );

            console.log(
                "C Priority Queue Output:",
                data.output
            );

            setTimeout(() => {

                ambulance.style.left = "78%";
                ambulance.style.top = "105px";

                log(
                    "C Priority Queue: Ambulance dispatched toward hospital."
                );

            }, 3000);

        } else {

            log(
                "Backend error: " + data.message
            );
        }

    } catch (error) {

        log(
            "Could not connect to C Priority Queue backend."
        );

        console.error(error);
    }
});

$("accidentBtn").addEventListener("click", async () => {

    if (state.accident) {
        log("Accident already active.");
        return;
    }

    state.accident = true;
    state.roadsOpen = 5;
    state.traffic = Math.min(100, state.traffic + 25);
    state.congestion = Math.min(100, state.congestion + 30);

    document.body.classList.add("closed");
    $("accidentMarker").style.display = "block";
    $("routeStatus").textContent =
        "Road closed — recalculate route";

    updateStats();

    log("ACCIDENT detected. Road closed.");

    // C GRAPH - ACCIDENT
    try {

        const response = await fetch(
            "http://127.0.0.1:5000/city?command=accident"
        );

        const data = await response.json();

        if (data.status === "success") {

            log(
                "C Backend: Graph processed the accident scenario."
            );

            log(
                "C Backend: Closed roads are ignored by Dijkstra."
            );

            console.log(
                "C Graph Output:",
                data.output
            );

        } else {

            log(
                "Backend error: " + data.message
            );
        }

    } catch (error) {

        log(
            "Could not connect to C Graph backend."
        );

        console.error(error);
    }


    // C MAX HEAP - CONGESTION
    try {

        const congestionResponse = await fetch(
            "http://127.0.0.1:5000/city?command=congestion"
        );

        const congestionData =
            await congestionResponse.json();

        if (congestionData.status === "success") {

            log(
                "C Max Heap: Congestion levels updated."
            );

            console.log(
                "C Max Heap Output:",
                congestionData.output
            );

        } else {

            log(
                "Max Heap backend error: " +
                congestionData.message
            );
        }

    } catch (error) {

        log(
            "Could not connect to C Max Heap backend."
        );

        console.error(error);
    }


    log(
        "Congestion increased; Max Heap monitors the affected road."
    );

});

$("openBtn").addEventListener("click", async () => {

    state.accident = false;
    state.roadsOpen = 6;
    state.congestion = Math.max(20, state.congestion - 25);
    state.traffic = Math.max(20, state.traffic - 15);

    document.body.classList.remove("closed");
    $("accidentMarker").style.display = "none";
    $("routeStatus").textContent = "Road open";

    updateStats();

    try {

        const response = await fetch(
            "http://127.0.0.1:5000/city?command=open"
        );

        const data = await response.json();

        if (data.status === "success") {

            log(
                "C Backend: Road reopened and Graph restored."
            );

            console.log(
                "C Graph Output:",
                data.output
            );

        } else {

            log(
                "Backend error: " + data.message
            );
        }

    } catch (error) {

        log(
            "Could not connect to C Graph backend."
        );

        console.error(error);
    }
});

$("resetBtn").addEventListener("click", () => {
    state.traffic = 32;
    state.roadsOpen = 6;
    state.congestion = 32;
    state.accident = false;
    state.emergency = false;

    $("accidentMarker").style.display = "none";
    $("ambulance").style.display = "none";
    $("routeLine").style.display = "none";
    document.body.classList.remove("closed", "route-active");
    $("routeStatus").textContent = "Ready";
    $("objectInfo").textContent = "Click a building on the city map.";
    updateStats();
    log("Simulation reset.");
});

updateStats();
log("Nova City initialized.");
log("Graph, Queue, Priority Queue, Heap and Hash Map ready.");
