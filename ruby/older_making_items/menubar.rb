require 'tk'

root =TkRoot.new
root.title='Window'

menu_click = Proc.new{
 Tk.messageBox({
  'type' => 'ok',
  'icon' => 'info',
  'title' => 'Title',
 'message' => 'Message'
 })
}

file_menu=TkMenu.new(root)

for menu_label in %w|New... Open.... Close Save Save\ As... Exit|
file_menu.add('command',
              'label'=> menu_label,
              'command'=> menu_click,
              'underline' =>0)
end

menu_bar = TkMenu.new
menu_bar.add('cascade',
             'menu' =>file_menu,
             'label' => 'File')

root.menu(menu_bar)

Tk.mainloop
