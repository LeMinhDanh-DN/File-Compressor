const express = require('express')
const port = 8080;
const app = express();

app.use(express.static('public'));

app.get('/',(req,res)=>{
  res.sendFile(__dirname + '/public/index.html');
});

app.listen(port,()=>{
  console.log(`Ứng dụng nén file đang chạy tại http://localhost:${port}`);
})