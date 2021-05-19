function main()
{
	//step-1 get canvas from dom
	var canvas = document.getElementById("MyID");

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
	var context = canvas.getContext("2d");

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

	//centre the text
	context.textAllign = "center"; //horrizontal center
	context.textBaseline = "middle"; //verticle center

	//font
	context.font = "30px sans-serif";

	//string to be display
	var str = "Hello World!!!";

	//text color
	context.fillStyle = "white";

	//display the text
	context.fillText(str, canvas.width/2, canvas.height/2);

	window.addEventListener("keydown", keyDown, false);
	window.addEventListener("click", mouseDown, false);
}

	function keyDown(event)
	{
		alert("key is pressed");
	}

	function mouseDown()
	{
		alert("mouse button is clicked");
	}
