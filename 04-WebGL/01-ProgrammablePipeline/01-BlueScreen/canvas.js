
var canvas = null;
var gl = null;

var canvas_original_width;
var canvas_original_hight;

var bFullscreen = false;

var requestAnimationFrame =
					window.requestAnimationFrame		||
					window.webkitRequestAnimationFrame	||
					window.mozRequestAnimatonFrame		||
					window.oRequestAnimationFrame		||
					window.msRequestAnimationFrame;

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

	canvas_original_width = canvas.width;
	canvas_original_hight = canvas.height;

	window.addEventListener("keydown", keyDown, false);
	window.addEventListener("click", mouseDown, false);
	window.addEventListener("resize", resize, false);

	init();

	//warm up resize call
	resize();

	//warm up display call
	display();
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
		bFullscreen = true;
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
		bFullscreen = false;
	}
}

function keyDown(event)
{
	//code
	switch(event.keyCode)
	{
		case 70:
		toggleFullScreen();
		break;

		default:
		break;
	}
}

function mouseDown()
{
	//code
}

function init()
{
	//get drawing context from canvas
	 gl = canvas.getContext("webgl2");

	if(!gl)
	{
		console.log("Obtaining WebGL context Failed!");	
	}
	else
	{
		console.log("Obtaining WebGL context Succeded");
	}

	gl.viewportWidth = canvas.width;
	gl.viewportWidth = canvas.height;

	gl.clearColor(0.0, 0.0, 1.0, 1.0);//blue color
}

function resize()
{
	//code
	if(bFullscreen == true)
	{
		canvas.width = window.innerWidth;
		canvas.height = window.innerHeight;
	}
	else
	{
		canvas.width = canvas_original_width;
		canvas.height = canvas_original_hight;
	}

	gl.viewport(0, 0, canvas.width, canvas.height);
}

function display()
{
	//code
	gl.clear(gl.COLOR_BUFFER_BIT);

	requestAnimationFrame(display, canvas);
}
