import lldb

def print_token_list(frame:lldb.SBFrame, bp_loc, internal_dict):
	error:lldb.SBValue = frame.EvaluateExpression('error')

	print('error : ', error.unsigned)

	head = frame.EvaluateExpression('token_list')
	if head.unsigned == 0:
		print('NULL list')
		print('')
		return
	watched:lldb.SBValue = head
	while watched.unsigned != 0:
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 1:
			print('DLESS', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 2:
			print('DGREAT', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 3:
			print('LESS', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 4:
			print('GREAT', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 5:
			print('PIPE', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 6:
			print('TEXT', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 7:
			print('QUOTED', end=" : ")
		if watched.GetChildMemberWithName('data').GetChildMemberWithName('type').unsigned == 8:
			print('DQUOTED', end=" : ")

		if watched.GetChildMemberWithName('data').GetChildMemberWithName('data') != 0:
			print(watched.GetChildMemberWithName('data').GetChildMemberWithName('data'))
		else:
			print('NULL')
		
		watched = watched.GetChildMemberWithName('next')
	print('')