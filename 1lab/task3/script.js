const strokeColor = "#000"
const fillColor = "#e70505"
const canvas = document.getElementById('canvas')

let center = {x: 0, y: 0}

function secondClick(event)
{
    const radius = Math.sqrt(Math.pow(center.x - event.clientX, 2) + Math.pow(center.y - event.clientY, 2))
    drawAndFillCircle(canvas, radius, center)

    canvas.removeEventListener('click', secondClick)
    canvas.addEventListener('click', firstClick)
}

function firstClick(event)
{
    center = {x: event.clientX, y: event.clientY}

    canvas.removeEventListener('click', firstClick)
    canvas.addEventListener('click', secondClick)
}


canvas.addEventListener('click', firstClick)






