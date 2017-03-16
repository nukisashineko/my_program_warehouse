require 'tk'

$resultsVar = TkVariable.new
root = TkRoot.new
root.title = "Window"
myFont = TkFont.new("family" => 'HuiFont', 
                    "size" => 20, 
                    "weight" => 'bold')
Lbl = TkLabel.new(root) do
  textvariable
  borderwidth 5
  font myFont
  foreground  "red"
  relief      "groove"
  pack("side" => "right",  "padx"=> "50", "pady"=> "50")
end

Lbl['textvariable'] = $resultsVar
$resultsVar.value = 'New value to display'

Tk.mainloop
