import("core.project.project")

function main(...)
    local args = {...}
    local target_name = args[1] or "app"
    local target = project.target(target_name)
    if not target then
        print(string.format("Target '%s' does not exist!", target_name))
        return
    end
    local bin_out = target:targetdir() .. "/" .. target:basename() .. ".bin"
    print(string.format("Target '%s' !", bin_out))
    os.exec("tsc-cli flash " .. bin_out)
end
