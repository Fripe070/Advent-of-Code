def calculate(equation, opp_last)
    if opp_last 
        opp = equation.last
        nums = equation[0..-2].map { |v| v.to_i }
    else
        opp = equation.first
        nums = equation[1..-1].map { |v| v.to_i }
    end
    if opp == "+" then
        return nums.reduce do |total, value| total + value end
    elsif opp == "*" then
        return nums.reduce do |total, value| total * value end
    end
end

content = File.read(ARGV.first)

p1_columns = []
content.gsub(/ +/, " ").each_line(chomp: true) { |line|
    line.strip.each_line(" ", chomp: true).with_index { |part, index| 
        (p1_columns[index] ||= []) << part
    } 
}
part1 = p1_columns.map {|eq| calculate(eq, true)} .reduce do |total, value| total + value end
print "Part 1: " + String(part1) + "\n"


lines = content.each_line(chomp: true)

space_columns = lines.first.each_char.with_index.select { |char, index|
    lines.all? { |line| line[index] == " " }
}.map { |char, index|
    index
}

problem_groups = []
problem_group_index = 0
lines.first.each_char.with_index { |char, index|
    if space_columns.include? index
        problem_group_index += 1
    end
    arr = (problem_groups[problem_group_index] ||= [])
    number = ""
    lines.each { |line|
        l_char = line[index]
        if /[0-9]/.match(l_char) 
            number += l_char
        end
        if ["+", "*"].include? l_char 
            arr << l_char
        end
    }
    if number != ""
        arr << number
    end
}
part2 = problem_groups.map { |eq| 
    calculate(eq, false)
}.reduce do |total, value| 
    total + value 
end
print "Part 2: " + String(part2) + "\n"
