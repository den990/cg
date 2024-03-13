document.addEventListener('DOMContentLoaded', function () {
    const fileInput = document.getElementById('fileInput');
    const imageContainer = document.getElementById('imageContainer');
    const imageView = document.getElementById('imageView');
    const image = document.getElementById('image');
    const iconClose = document.querySelector('.close__block');

    fileInput.addEventListener('change', function (event) {
        const file = event.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = function (e) {
                const tempImage = new Image();
                tempImage.src = e.target.result;

                tempImage.onload = function() {
                    const imageWidth = tempImage.width;
                    const imageHeight = tempImage.height;

                    image.src = e.target.result;

                    if (imageHeight >= imageContainer.clientHeight || imageWidth >= imageContainer.clientWidth) {
                        centerImage();
                    }
                    else
                    {
                        image.style.width = imageWidth + 'px';
                        image.style.height = imageHeight + 'px';
                    }
                    imageView.classList = 'active';
                    iconClose.style.display = 'flex';
                };
            };
            reader.readAsDataURL(file);
        }
    });


    iconClose.addEventListener('click', function (event) {
        event.preventDefault()
        image.src = 'download-svgrepo-com.svg'
        image.style.width = '50px';
        image.style.height = '50px';
        iconClose.style.display = 'none';
        imageView.classList = 'inactive';
        imageView.style.removeProperty('left');
        imageView.style.removeProperty('top');
    })




    window.addEventListener('resize', function () {
        centerImage();
    });

    function centerImage() {

        const containerWidth = imageContainer.clientWidth;
        let containerHeight =  imageContainer.clientHeight;

        const imageNaturalWidth = image.naturalWidth;
        const imageNaturalHeight = image.naturalHeight;

        let targetWidth = 0.8 * containerWidth;
        let targetHeight = (targetWidth / imageNaturalWidth) * imageNaturalHeight;

        if (targetHeight > containerHeight)
        {
            let index = 7;//wtf
            while(targetHeight > containerHeight)
            {
                targetWidth = index / 10 * containerWidth;//wtf
                targetHeight = (targetWidth / imageNaturalWidth) * imageNaturalHeight;
                index--;
            }
        }

        image.style.width = targetWidth + 'px';
        image.style.height = targetHeight + 'px';

        const offsetTop = (imageContainer.clientHeight - imageView.clientHeight) / 2;
        const offsetLeft = (imageContainer.clientWidth - imageView.clientWidth) / 2;

        imageContainer.scrollTo(offsetLeft, offsetTop);
    }

    imageContainer.addEventListener('click', function () {
        if (imageView.classList.contains('inactive')) {
            fileInput.click();
        }
        else
        {
            if (imageView.classList.contains('active')) {
                dragAndDrop(imageView);
            }
        }
    });

});

function dragAndDrop(element) {
    let offsetX, offsetY, isDragging = false;

    element.addEventListener('mousedown', function (event) {
        isDragging = true;

        offsetX = event.clientX - element.getBoundingClientRect().left;
        offsetY = event.clientY - element.getBoundingClientRect().top;

        // Prevent default dragging behavior
        event.preventDefault();
    });

    window.addEventListener('mousemove', function (event) {
        if (isDragging) {
            const x = event.clientX - offsetX;
            const y = event.clientY - offsetY;

            // Set the new position of the element
            element.style.left = x + 'px';
            element.style.top = y + 'px';
        }
    });

    window.addEventListener('mouseup', function () {
        isDragging = false;
    });
}
