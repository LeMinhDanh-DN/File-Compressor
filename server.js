const express = require('express')
const multer = require('multer')
const port = 8080;
const app = express();
const upload = multer({dest : "uploads/"});

app.use(express.static('public'));
app.use(express.json());

app.get('/',(req,res)=>{
  res.sendFile(__dirname + '/public/index.html');
});

app.post('/upload', upload.single("fileUpload"), (req,res)=>{
  
  res.status(200).json({
    messsage : "successful in uploading",
    fileUpload: req.file,
    action: req.body
  })
});

app.listen(port,()=>{
  console.log(`Ứng dụng nén file đang chạy tại http://localhost:${port}`);
})

