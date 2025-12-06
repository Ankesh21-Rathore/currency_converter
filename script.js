document.getElementById('convertBtn').addEventListener('click', function() {
    const amount = document.getElementById('amount').value;
    const from = document.getElementById('from').value;
    const to = document.getElementById('to').value;

    if(amount === "" || isNaN(amount)) {
        alert("Please enter a valid number");
        return;
    }

    fetch(`http://localhost:8080/convert?amount=${amount}&from=${from}&to=${to}`)
    .then(response => response.json())
    .then(data => {
        if(data.result) {
            const converted = parseFloat(data.result).toFixed(2);
            document.getElementById('result').innerText = `${amount} ${from} = ${converted} ${to}`;
        } else {
            document.getElementById('result').innerText = "Error: " + data.error;
        }
    })
    .catch(err => {
        console.error(err);
        document.getElementById('result').innerText = "Error converting currency";
    });
});
