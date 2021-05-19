
var canvas = null;
var context = null;

function main()
{
	//code
	//step-1 get canvas from dom
	canvas = document.getElementById("MyID");

	if(!canvas)
	{
		console.log("Obtaining Canvas Failed!");
	}
	else
	{
		console.log("Obtaining Canvas Succeded");
	}

	//retrive width and hight of canvas
	console.log("Canvas Width = " + canvas.width);
	console.log("\n Canvas hight = " + canvas.height);

	//get drawing context from canvas
	context = canvas.getContext("2d");

	if(!context)
	{
		console.log("Obtaining context Failed!");
	}
	else
	{
		console.log("Obtaining context Succeded");
	}

	//paint backgroud by black color
	//context.fillStyle = "black";
	context.fillRect(0, 0, canvas.width, canvas.height);

	window.addEventListener("keydown", keyDown, false);
	window.addEventListener("click", mouseDown, false);

	drawText("Hello World!!!");
}

function keyDown(event)
{
	//code
	switch(event.keyCode)
	{
		case 70:
		toggleFullScreen();
		drawText("Hello World!!!");
		break;

		default:
		break;
	}
}

function mouseDown()
{
	//code
}

function toggleFullScreen()
{
	//code
	var fullscreen_element =
				document.fullscreenElement			||
				document.webkitFullscreenElement	||
				document.mozFullScreenElement		||
				document.msFullscreenElement		||
				null;

	if(fullscreen_element == null)
	{
		if(canvas.requestFullscreen)
		{
			canvas.requestFullscreen();
		}
		else if(canvas.webkitRequestFullscreen)
		{
			canvas.webkitRequestFullscreen();
		}
		else if(canvas.mozRequestFullScreen)
		{
			canvas.mozRequestFullScreenElement();
		}
		else if(canvas.msRequestFullscreen)
		{
			canvas.msRequestFullscreen();
		}
	}
	else
	{
		if(document.exitFullscreen)
		{
			document.exitFullscreen();
		}
		else if(document.webkitExitFullscreen)
		{
			document.webkitExitFullscreen();
		}
		else if(document.mozCancelFullScreen)
		{
			document.mozCancelFullScreen();
		}
		else if(document.msExitFullscreen)
		{
			document.msExitFullscreen();
		} 
	}
}

function drawText(text)
{
	//code
	//centre the text
	context.textAllign = "center"; //horrizontal center
	context.textBaseline = "middle"; //verticle center

	//font
	context.font = "30px sans-serif";

	//text color
	context.fillStyle = "white";

	//display the text
	context.fillText(text, canvas.width/2, canvas.height/2);
}
