const express = require('express')
const multer = require('multer')
const {execFile} = require('child_process'); //mot ham  de thuc thi file exe ben ngoai
const path = require('path');
const fs = require('fs');
const { argv, stdout } = require('process');
const port = 8080;
const app = express();
const tool = path.join(__dirname, 'compressor_tool.exe');

const storage = multer.diskStorage({
    destination: (req, file, cb) =>{
        cb(null, 'uploads/');
    },
    filename: (req, file, cb)=>{
        cb(null, Date.now() + '-' + file.originalname) //file.originalname se co jpg.,,,
    }
}); 

const upload = multer({storage: storage});

app.use(express.static('public'));
app.use(express.json()); // chi dung khi fe gui len application/json

app.get('/',(req,res)=>{
    res.sendFile(__dirname + '/public/index.html');
});

app.post('/upload', upload.single("fileUpload"), (req,res)=>{

    let argvs = [];
    let inputF = req.file.path;
    let outputF;

    if(req.body.action == 'compress'){
        argvs.push('-c');
        outputF = path.join(req.file.destination,
                            path.parse(req.file.originalname).name + '.bin');
    }
    else if(req.body.action == 'decompress'){
        argvs.push('-d');
        outputF = path.join(req.file.destination,
                            'restored-'+req.file.originalname);
    }

    argvs.push(inputF);
    argvs.push(outputF);

    const options = {maxBuffer: 1024*1024*5}
    // connect with c++
    execFile(tool, argvs, options, (error, stdout, stderr) =>{ //callback
        if(error){
            console.error(error);
            console.error(stderr);

            res.status(500).send("Server error cant call compressor-tool");
        }
        console.log("c++ inform", stdout);

        if(fs.existsSync(outputF)){
            res.download(outputF, 'dataZip');
        }
        else{
            res.send("tool run compeletely but cant find the file result");
        }
    });
});

app.listen(port,()=>{
    console.log(`Ứng dụng nén file đang chạy tại http://localhost:${port}`);
})
