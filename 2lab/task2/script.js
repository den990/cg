const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');
const fileInput = document.getElementById('fileInput');
const colorPicker = document.getElementById('colorPicker');
let painting = false;

function newFile() {
    context.clearRect(0, 0, canvas.width, canvas.height);
}

function openFile() {
    fileInput.click();
}

function saveAs(format) {
    let fileName = 'drawing';
    switch (format) {
        case 'png':
            fileName += '.png';
            saveFile("image/png", fileName);
            break;
        case 'bmp':
            fileName += '.bmp';
            saveFile("image/bmp", fileName);
            break;
        case 'jpeg':
            fileName += '.jpg';
            saveFile("image/jpeg", fileName);
            break;
    }
}

function saveFile(format, fileName) {
    let dataUrl;
    if (format === 'image/jpeg')
    {
        const tempCanvas = document.createElement('canvas');
        const tempContext = tempCanvas.getContext('2d');
        tempCanvas.width = canvas.width;
        tempCanvas.height = canvas.height;

        tempContext.fillStyle = '#ffffff'; //для jpg
        tempContext.fillRect(0, 0, tempCanvas.width, tempCanvas.height);

        tempContext.drawImage(canvas, 0, 0);

        // Сохраняем временное изображение в нужном формате
        dataUrl = tempCanvas.toDataURL(format);
    }
    else {
        dataUrl = canvas.toDataURL(format);
    }
    const a = document.createElement('a');
    a.href = dataUrl;
    a.download = fileName;
    a.click();
}

fileInput.addEventListener('change', function (e) {
    const file = e.target.files[0];
    const reader = new FileReader();

    reader.onload = function (event) {
        const img = new Image();
        img.onload = function () {

            canvas.width = img.width;
            canvas.height = img.height;

            canvas.style.maxHeight = '90vh'
            canvas.style.margin = 'auto';

            context.clearRect(0, 0, canvas.width, canvas.height);
            context.drawImage(img, 0, 0, canvas.width, canvas.height);
        };
        img.src = event.target.result;
    };

    reader.readAsDataURL(file);
});


canvas.addEventListener('mousedown', startPosition);
canvas.addEventListener('mouseup', endPosition);
canvas.addEventListener('mousemove', draw);

function startPosition(e) {
    painting = true;
    draw(e);
}

function endPosition() {
    painting = false;
    context.beginPath();
}

function draw(e) {
    if (!painting) return;

    const rect = canvas.getBoundingClientRect();
    const scaleX = canvas.width / rect.width;
    const scaleY = canvas.height / rect.height;

    context.lineWidth = 3;
    context.lineCap = 'round';
    context.strokeStyle = colorPicker.value;

    context.lineTo((e.clientX - rect.left) * scaleX, (e.clientY - rect.top) * scaleY);
    context.stroke();
    context.beginPath();
    context.moveTo((e.clientX - rect.left) * scaleX, (e.clientY - rect.top) * scaleY);
}


//

// const file = event.target.files[0];
// if (file) {
//     const reader = new FileReader();
//     reader.onload = function (e) {
//         const tempImage = new Image();
//         tempImage.src = e.target.result;
//
//         tempImage.onload = function() {
//             const imageWidth = tempImage.width;
//             const imageHeight = tempImage.height;
//
//             image.src = e.target.result;
//
//             if (imageHeight >= imageContainer.clientHeight || imageWidth >= imageContainer.clientWidth) {
//                 centerImage();
//             }
//             else
//             {
//                 image.style.width = imageWidth + 'px';
//                 image.style.height = imageHeight + 'px';
//             }
//             imageView.classList = 'active';
//             iconClose.style.display = 'flex';
//         };
//     };
//     reader.readAsDataURL(file);
// }
