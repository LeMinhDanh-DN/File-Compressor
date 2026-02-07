fetch('http://localhost:8080/', {
  method: 'POST',
  headers: {
    'Content-Type': 'application/json'
  },
  body: JSON.stringify({ a: 1, b: 2 })
});
