const fileInput = document.getElementById('fileInput');
const dropZone = document.getElementById('drop-zone');
const fileNameDisplay = document.getElementById('file-name');

// Khi click vào vùng upload thì mở cửa sổ chọn file
dropZone.addEventListener('click', () => fileInput.click());

// Khi file được chọn thì hiện tên file lên
fileInput.addEventListener('change', () => {
    if (fileInput.files.length > 0) {
        fileNameDisplay.innerHTML = "File đã chọn: " + fileInput.files[0].name;
        dropZone.classList.add('active'); 
    }
});

const uploadBtn = document.querySelector('#btn-process');
uploadBtn.addEventListener('click',()=>{
    const file = fileInput.files[0];
    const radios = document.getElementsByName('action');
    let type;

    radios.forEach((radio) =>{
        if(radio.checked){
            type = radio.value;
        }
    });
    const formData = new FormData(); // co the chua duoc file

    formData.append('fileUpload', file);
    formData.append('action',type);

    console.log(type);
    fetch('http://localhost:8080/upload', {
        method: 'POST',
        body: formData

    })
    .then(res => res.json())
    .then(data => console.log(data));
});