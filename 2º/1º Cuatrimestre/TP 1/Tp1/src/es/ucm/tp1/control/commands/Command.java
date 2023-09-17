package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.logic.Game;

public abstract class Command {

	private static final String UNKNOWN_COMMAND_MSG = "Unknown command";

	protected static final String INCORRECT_NUMBER_OF_ARGS_MSG = "Incorrect number of arguments";

	/* @formatter:off */
	protected static final Command[] AVAILABLE_COMMANDS = {
		new HelpCommand(),
		new InfoCommand(),
		new UpdateCommand(),
		new MoveUpCommand(),
		new MoveDownCommand(),
		new ExitCommand(),
		new ResetCommand(),
		new TestCommand(),
		new ShootCommand(),
		new GrenadeCommand(),
		new WaveCommand(),
		new SerializeCommand(),
		new SaveCommand(),
		new DumpCommand(),
		new ShowRecordCommand(),
		new ClearCommand(),
		new CheatCommand()
	};
	/* @formatter:on */

	public static Command getCommand(String[] commandWords) throws CommandParseException{
		Command command = null;
		int i = 0;
		boolean encontrado = false;
		
		while(i < Command.AVAILABLE_COMMANDS.length && !encontrado) {
			
			command = AVAILABLE_COMMANDS[i].parse(commandWords);
			
			if(command != null) encontrado = true;
			else i++;
			
		}
		
		if(command == null) throw new CommandParseException(String.format("[ERROR]: %s", UNKNOWN_COMMAND_MSG));
		
		return command;
	}

	private final String name;

	private final String shortcut;

	private final String details;

	private final String help;

	public Command(String name, String shortcut, String details, String help) {
		this.name = name;
		this.shortcut = shortcut;
		this.details = details;
		this.help = help;
	}

	public abstract boolean execute(Game game) throws CommandExecuteException;

	protected boolean matchCommandName(String name) {
		return this.shortcut.equalsIgnoreCase(name) || this.name.equalsIgnoreCase(name);
	}

	protected Command parse(String[] words) throws CommandParseException{
		
		if (matchCommandName(words[0])) {
			
			if (words.length != 1) {
				throw new CommandParseException(String.format("[ERROR]: Command %s: %s", name, INCORRECT_NUMBER_OF_ARGS_MSG));
			} else {
				return this;
			}
		}
		
		return null;
		
	}

	protected String helping() {
		
		StringBuilder buffer = new StringBuilder("Available commands: \n");
		
		for(int i = 0; i < Command.AVAILABLE_COMMANDS.length; i++) {
			
			buffer
			.append(Command.AVAILABLE_COMMANDS[i].details)
			.append(": ")
			.append(Command.AVAILABLE_COMMANDS[i].help)
			.append("\n");
		}
		
		return buffer.toString();
	}

}
