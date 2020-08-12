package Scheduler;

import java.util.Arrays;
import java.util.Scanner;

public class Scheduler {
	
	private int capacity = 10;
	// �迭�� �� ĭ�� Event Ÿ��. ���⼭ �������� ����ȴ�.(����Ŭ������ �θ�Ŭ������ ��� ����)
	// �� ������ Ÿ���� �ִٰ� �ؼ� ���� �ٸ� �迭�� �����ʿ� ����, ��� �� �� �ִ�(�ڹ��� ����!!)(C�� �ٸ���..)
	public Event []events = new Event[capacity];
	public int n=0;
	private Scanner kb;
	
	public void processCommand() {
		kb = new Scanner(System.in);
		while(true) {
			System.out.print("$ ");
			String command = kb.next();
			if(command.equals("addevent")) {
				String type = kb.next();
				if(type.equalsIgnoreCase("oneday"))
					handleAddOneDayEvent();
				else if (type.equalsIgnoreCase("duration"))
					handleAddDurationEvent();
				else if(type.equalsIgnoreCase("deadline"))
					handleAddDeadlineEvent();			
				
			}else if(command.equals("list")) {
				handleList();
				
			}else if(command.equals("show")) {
				handleShow();
				
			}else if(command.equals("sort")) {
				Arrays.sort(events,0,n);  // �� �� generic ��.
			}else if(command.equals("exit")) {
				break;		
			}
		}
		
	}
	private void handleShow() {
		String dateString = kb.next();
		MyDate theDate = parseDateString(dateString);
		for(int i=0;i<n;i++) {
			// test if events[i] is relevant to the date, then print it;
			if((events[i]).isRelevant(theDate))
				System.out.println(events[i].toString());
		}
		
	}
	private void handleList() {
		for(int i=0;i<n;i++) {
			System.out.println("  "+events[i].toString());
		}
		
	}
	private void handleAddDeadlineEvent() {
		System.out.print("  deadline: ");
		String dateString = kb.next();
		System.out.print("  title: ");
		String title = kb.next();
		
		MyDate date = parseDateString(dateString);
		DeadlinedEvent ev = new DeadlinedEvent(title,date);
		addEvent(ev);
		
	}
	private void handleAddDurationEvent() {
		System.out.print("  begin: ");
		String beginString = kb.next();
		System.out.print("  end: ");
		String endString = kb.next();
		System.out.print("  title: ");
		String title = kb.next();
		
		MyDate begin = parseDateString(beginString);
		MyDate end = parseDateString(endString);
		
		DurationEvent ev = new DurationEvent(title,begin,end);
		addEvent(ev);
		
	}
	private void handleAddOneDayEvent() {
		System.out.print("	when: ");
		String dateString = kb.next();
		
		System.out.print("	title: ");
		String title = kb.next();
		
		MyDate date = parseDateString(dateString);
		OneDayEvent ev = new OneDayEvent(title, date);
		System.out.println(ev.toString());
		
		addEvent(ev);
		
	}
	private void addEvent(Event ev) {
		if(n>=capacity)
			reallocate(); // �ڹٿ��� �������ִ� �޼��� �� �ϳ�!
		events[n++] = ev; // ���⼭ ������ ����!! OneDayEvent Ÿ���� ��ü�� EventŸ���� �迭�� ������!		
	}
	private void reallocate() {
		Event []tmp = new Event[capacity * 2];
		for(int i=0;i<n;i++)
			tmp[i] = events[i];
		events = tmp;
		capacity *= 2;
	}
	private MyDate parseDateString(String dateString) {
		String []tokens = dateString.split("/");
		int year = Integer.parseInt(tokens [0]);
		int month = Integer.parseInt(tokens[1]);
		int day = Integer.parseInt(tokens[2]);
		
		MyDate d = new MyDate(year,month,day);
		return d;
	}
	public static void main(String[] args) {
		Scheduler app = new Scheduler();
		app.processCommand();
		
	}

}
