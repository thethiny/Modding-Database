Set WshShell = WScript.CreateObject("WScript.Shell")

' Filling CRNs

CRNs = InputBox("How Many Courses?" & vbNewLine & "Maximum 10", "Course Registrar")
Dim arr(9)

For i = 0 to CRNs-1
arr(i) = InputBox("Input CRN Number " & i+1, "Course Registrar")
Next



' WshShell.Run("https://uos.sharjah.ac.ae:9050/prod_enUS/twbkwbis.P_GenMenu?name=bmenu.P_RegMnu")
If MsgBox("Go to the registration page, click ok after clicking the first box." & vbNewLine & vbNewLine & "Press No To Cancel", vbYesNo + vbQuestion + vbSystemModal, "WhatsApp DDos") = vbYes Then

' Filling
For i = 0 to CRNs-1
WshShell.SendKeys arr(i)
WScript.Sleep 5
WshShell.SendKeys "{TAB}"
WScript.Sleep 5
Next

' Tabbing then Enter
For i = CRNs to 9
WshShell.SendKeys "{TAB}"
Next

WshShell.SendKeys "{Enter}"


End if